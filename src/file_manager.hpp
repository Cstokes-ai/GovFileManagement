
#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP
#include <string>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm> // for std::min
#include <openssl/aes.h>
#include <openssl/rand.h>
#include "crypto.hpp"


class file_manager {
    public:
    void uploadFile(const std::string& filePath);
    void downloadFile(const std::string &fileName, const std:: string &destinationPath);
    void deleteFile(const std::string &fileName);
    void listFiles() const;
    void getFileInfo(const std::string &fileName) const;// file ownership, upload date, size, etc.
    void permissions(const std::string &fileName, const std::string &permissionType);// this is for reading and writing to a file/who has access to it

};
#endif // FILE_MANAGER_HPP