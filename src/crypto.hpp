/*

crypto.cpp / crypto.hpp
Start here.

Implement AES-256 encryption and decryption using OpenSSL.

Test encryption with small test files.

Focus on:

encrypt_file(input_path, output_path)

decrypt_file(encrypted_path, output_path)



*/

#ifndef CRYPTO_HPP
#define CRYPTO_HPP
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <string>
#include <stdexcept>
#include <fstream>
#include <vector>
// this is for defining functions only

class Crypto {
    public:
    void encryption(const std::string& input_path, const std::string& output_path);
    void decryption(const std::string& encrypted_path, const std::string& output_path);
};

#endif // CRYPTO_HPP
