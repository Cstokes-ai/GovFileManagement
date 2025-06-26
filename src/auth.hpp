// auth.cpp / auth.hpp
//- User registration, login verification, and password hashing.


#ifndef AUTH_HPP
#define AUTH_HPP
#include <string>
#include <stdexcept>
#include <iostream>
#include <memory>
#include <pqxx/pqxx>
#include "crypto.hpp"
// this file is just declaring functions
class Authentication {
    public:
        // Register a new user
        void registerUser(const std::string &username, const std::string &password);

        // Verify user login credentials
        bool verifyLogin(const std::string &username, const std::string &password);

        // Hash a password securely
        std::string hashPassword(const std::string &password);

        // Verify a password against a hashed password
        bool verifyPassword(const std::string &password, const std::string &hashedPassword);

        // Reset a user's password
        void resetPassword(const std::string &username, const std::string &newPassword);

        // Generate a secure token for password reset
        std::string generateResetToken(const std::string &username);

        // Validate a password reset token
        bool validateResetToken(const std::string &username, const std::string &token);
};



#endif // AUTH_HPP