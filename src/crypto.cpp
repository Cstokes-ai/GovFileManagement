// this is the crypto.cpp file
#include "crypto.hpp"
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <cstring>


class Crypto {
    public:
    void encryption(const std::string& input_path, const std::string& output_path){
        // this function encrypts the file at input before storage
        AES_KEY encryption_key;
        unsigned char key[AES_BLOCK_SIZE] = {0}; // AES_BLOCK_SIZE is 16 bytes
        unsigned char iv[AES_BLOCK_SIZE] = {0}; // Initialization vector
        //generate a random key
        if (!RAND_bytes(key, sizeof(key))) {
            throw std::runtime_error("Failed to generate random key");

        }
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
    }
    /*
    
    Securely handle or store the key and IV so you can decrypt later (or pass them to the decryption function as needed).
Implement the decryption function to reverse the process: read t
he encrypted file, decrypt it with the correct key/IV, and write the original data to an output file.
Handle errors and edge cases (file not found, encryption/decryption failures, etc.).

    */
}