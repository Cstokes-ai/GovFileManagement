#include <string>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdio> // for std::remove
#include <filesystem>
#include <algorithm> // for std::min
#include <openssl/aes.h>
#include <openssl/rand.h>
#include "crypto.hpp"
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h> // For access, R_OK, W_OK

// Ensure all string literals are explicitly suffixed with std::string_literals where needed.

// Ensure all files communicate properly
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
        for (const auto& entry : std::filesystem::directory_iterator(".")) {
            if (entry.is_regular_file()) {
                std::cout << entry.path().filename().string() << std::endl;
            }
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
    void permissions(const std::string &fileName, const std::string &permissionType) {
        std::string encFile = fileName + ".enc";
        std::filesystem::perms p = std::filesystem::status(encFile).permissions();

        if (permissionType == "read") {
            if ((p & std::filesystem::perms::owner_read) != std::filesystem::perms::none) {
                std::cout << "Read permission granted for: " << encFile << std::endl;
            } else {
                std::cerr << "Read permission denied for: " << encFile << std::endl;
            }
        } else if (permissionType == "write") {
            if ((p & std::filesystem::perms::owner_write) != std::filesystem::perms::none) {
                std::cout << "Write permission granted for: " << encFile << std::endl;
            } else {
                std::cerr << "Write permission denied for: " << encFile << std::endl;
            }
        } else {
            throw std::invalid_argument("Invalid permission type. Use 'read' or 'write'.");
        }
        
    }

};
