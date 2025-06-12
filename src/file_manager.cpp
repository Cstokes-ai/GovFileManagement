#include <string>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cstdio> // for std::remove
#include <filesystem>
#include <algorithm> // for std::min
#include <openssl/aes.h>
#include <openssl/rand.h>
#include "crypto.hpp"
#include <dirent.h>
#include <sys/stat.h>
// all files communicate with one another for the application to work properly
using namespace std::string_literals;
std::vector<unsigned char> encrypt(const std::vector<char>& buffer);
std::vector<unsigned char> decrypt(const std::vector<char>& buffer);

class file_manager {

    void uploadFile(const std::string &filePath){
        std::ifstream file(filePath, std::ios::binary);
        if (!file) {
            throw std::runtime_error("Could not open file for reading: " + filePath);
        }

        // Read the file content
        std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();

        // Encrypt the file content
        std::vector<unsigned char> encryptedData = encrypt(buffer);

        // Save the encrypted data to a new file
        std::string encryptedFilePath = filePath + ".enc";
        std::ofstream outFile(encryptedFilePath, std::ios::binary);
        if (!outFile) {
            throw std::runtime_error("Could not open file for writing: " + encryptedFilePath);
        }
        outFile.write(reinterpret_cast<const char*>(encryptedData.data()), encryptedData.size());
        outFile.close();
    }
    void downloadFile(const std::string &fileName, const std::string &destinationPath) {
        std::ifstream file(fileName + ".enc", std::ios::binary);
        if (!file) {
            throw std::runtime_error("Could not open file for reading: " + fileName);
        }
        //make sure to download the file to the correct destination
        std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
        // Decrypt the file content
        std::vector<unsigned char> decryptedData = decrypt(buffer);
        // Save the decrypted data to the destination path
        std::ofstream outFile(destinationPath, std::ios::binary);
        if (!outFile) {
            throw std::runtime_error("Could not open file for writing: " + destinationPath);
        }
        outFile.write(reinterpret_cast<const char*>(decryptedData.data()), decryptedData.size());
        outFile.close();

            // also need to make sure to know if the file download is complete or throw an error.
            std::cout << "File downloaded successfully to " << destinationPath << std::endl;
            if (decryptedData.empty()) {
                throw std::runtime_error("Decrypted data is empty, download may have failed.");
            }   

    }
    void deleteFile(const std::string &fileName) {
        if (std::remove((fileName + ".enc").c_str()) != 0) {
            throw std::runtime_error("Could not delete file: " + fileName);
        }
        std::cout << "File deleted successfully: " << fileName << std::endl;
    }

    void listFile() const {
        std::cout << "Listing files in the current directory: " << std::endl;
        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir(".")) != nullptr) {
            while ((ent = readdir(dir)) != nullptr) {
                // Only print regular files (not directories)
                if (ent->d_type == DT_REG) {
                    std::cout << ent->d_name << std::endl;
                }
            }
            closedir(dir);
        } else {
            std::cerr << "Could not open current directory." << std::endl;
        }
    }
    void getFileInfo(const std::string &fileName) const {
        std::string encFile = fileName + ".enc";
        struct stat fileStat;
        if (stat(encFile.c_str(), &fileStat) != 0) {
            throw std::runtime_error("File does not exist: " + fileName);
        }
        std::cout << "File: " << encFile << std::endl;
        std::cout << "Size: " << fileStat.st_size << " bytes" << std::endl;
        std::cout << "Last modified: " << fileStat.st_mtime << std::endl;
    }
    void permissions(const std::string &fileName, const std::string &permissionType){
        std::string encFile = fileName + ".enc";
        if (permissionType == "read") {
            if (access(encFile.c_str(), R_OK) == 0) {
                std::cout << "Read permission granted for: " << encFile << std::endl;
            } else {
                std::cerr << "Read permission denied for: " << encFile << std::endl;
            }
        } else if (permissionType == "write") {
            if (access(encFile.c_str(), W_OK) == 0) {
                std::cout << "Write permission granted for: " << encFile << std::endl;
            } else {
                std::cerr << "Write permission denied for: " << encFile << std::endl;
            }
        } else {
            throw std::invalid_argument("Invalid permission type. Use 'read' or 'write'.");
        }
        
    }

};
