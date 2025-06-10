// this is the crypto.cpp file
#include "crypto.hpp"
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <cstring>
#include <algorithm> // for std::min


class Crypto {
    public:
    void encryption(const std::string& input_path, const std::string& output_path){
        AES_KEY encryption_key;
        unsigned char key[32] = {0}; // 256-bit key for AES-256
        unsigned char iv[AES_BLOCK_SIZE] = {0}; // Initialization vector

        // Generate a random key
        if (!RAND_bytes(key, sizeof(key))) {
            throw std::runtime_error("Failed to generate random key");

        }
        // Generate a random IV
        if (!RAND_bytes(iv, sizeof(iv))) {
            throw std::runtime_error("Failed to generate random IV");
        }
        //key handling, store it securely file.
        std::ofstream key_file("encryption_key.bin", std::ios::binary);
        if (!key_file) {
            throw std::runtime_error("Failed to open key file for writing");
        }
        key_file.write(reinterpret_cast<const char*>(key), sizeof(key));
        key_file.close();

        // Set the encryption keY
        if (AES_set_encrypt_key(key, 256, &encryption_key) < 0) {
            throw std::runtime_error("Failed to set encryption key");
        }
        // read the input files contents
        std:: ifstream input_file(input_path, std::ios::binary);
        if (!input_file) {
            throw std::runtime_error("Failed to open input file");
        }
        std::vector<unsigned char> buffer((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
        input_file.close();

        //write the encrypted contents to the output file
        std::ofstream output_file(output_path, std::ios::binary);
        if (!output_file) {
            throw std::runtime_error("Failed to open output file");
        }

        // Write IV at the beginning of the file for later decryption
        output_file.write(reinterpret_cast<const char*>(iv), AES_BLOCK_SIZE);

        // Encrypt the data in blocks
        size_t num_blocks = (buffer.size() + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE;
        for (size_t i = 0; i < num_blocks; ++i) {
            unsigned char block[AES_BLOCK_SIZE] = {0};
            size_t block_size = std::min(AES_BLOCK_SIZE, buffer.size() - i * AES_BLOCK_SIZE);
            std::memcpy(block, buffer.data() + i * AES_BLOCK_SIZE, block_size);
            AES_cbc_encrypt(block, block, AES_BLOCK_SIZE, &encryption_key, iv, AES_ENCRYPT);
            output_file.write(reinterpret_cast<const char*>(block), AES_BLOCK_SIZE);
        }
        output_file.close();

        // NOTE: In a real system, you must securely store or transmit the key and IV for decryption.
        // Here, the IV is stored at the start of the output file, but the key must be managed securely.
    }
    void decryption(const std::string& encrypted_path, const std::string& output_path) {
        AES_KEY decryption_key;
        unsigned char key[32] = {0}; // 256-bit key for AES-256
        unsigned char iv[AES_BLOCK_SIZE] = {0}; // Initialization vector

        // Read the IV from the beginning of the encrypted file
        std::ifstream input_file(encrypted_path, std::ios::binary);
        if (!input_file) {
            throw std::runtime_error("Failed to open encrypted file");
        }
        input_file.read(reinterpret_cast<char*>(iv), AES_BLOCK_SIZE);

        // Set the decryption key (the key must be securely managed)
        if (AES_set_decrypt_key(key, 256, &decryption_key) < 0) {
            throw std::runtime_error("Failed to set decryption key");
        }
        /*
        Key Retrieval:
Before setting the decryption key, you should:
Accept the key as a function parameter,
Or load it from a secure location (file, user input, etc.).
        */
       // in this i am loading the key from a file
       std::ifstream key_file("encryption_key.bin", std::ios::binary);
        if (!key_file) {
            throw std::runtime_error("Failed to open key file");
        }

        // Read the encrypted data
        std::vector<unsigned char> buffer((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
        input_file.close();

        // Write the decrypted contents to the output file
        std::ofstream output_file(output_path, std::ios::binary);
        if (!output_file) {
            throw std::runtime_error("Failed to open output file");
        }

        // Decrypt the data in blocks
        size_t num_blocks = (buffer.size() + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE;
        for (size_t i = 0; i < num_blocks; ++i) {
            unsigned char block[AES_BLOCK_SIZE] = {0};
            size_t block_size = std::min(AES_BLOCK_SIZE, buffer.size() - i * AES_BLOCK_SIZE);
            std::memcpy(block, buffer.data() + i * AES_BLOCK_SIZE, block_size);
            AES_cbc_encrypt(block, block, AES_BLOCK_SIZE, &decryption_key, iv, AES_DECRYPT);
            output_file.write(reinterpret_cast<const char*>(block), block_size);
        }
        output_file.close();
    }
    
};