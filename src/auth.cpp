#include <iostream>
#include "auth.hpp"
#include "database.hpp"
#include <stdexcept>
#include <pqxx/pqxx>
#include <memory>
#include "crypto.hpp"
#include <string>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <pqxx/transaction>
#include <pqxx/result>
#include <pqxx/row>
#include <pqxx/connection>
#include <pqxx/transaction_base>


class Auth {
    public:

    // Register a new user
    void registerUser(const std::string &username, const std::string &password) {
        validateInput(username, password);

        Database db;
        db.connect("host=localhost port=5432 dbname=yourdb user=youruser password=yourpass");

        auto user = db.fetchUserByUsername(username);
        if (!user.empty()) {
            throw std::runtime_error("Username already exists");
        }

        std::string hashPassword = Crypto::hashPassword(password);
        db.executeQuery("INSERT INTO users (username, password) VALUES ($1, $2)", {username, hashPassword});

        std::cout << "User registered successfully." << std::endl;
    }

    // Verify user login
    bool verifyLogin(const std::string &username, const std::string &password) {
        validateInput(username, password);

        Database db;
        db.connect("host=localhost port=5432 dbname=yourdb user=youruser password=yourpass");

        auto user = db.fetchUserByUsername(username);
        if (user.empty()) {
            throw std::runtime_error("User does not exist");
        }

        // Access the password field using the correct index
        std::string storedHashedPassword = user.at(1); // Assuming password is the second column
        return verifyPassword(password, storedHashedPassword);
    }

    // Verify a password against a hashed password
    bool verifyPassword(const std::string &password, const std::string &hashedPassword) {
        if (password.empty() || hashedPassword.empty()) {
            throw std::invalid_argument("Password and hashed password cannot be empty");
        }

        return Crypto::hashPassword(password) == hashedPassword;
    }

    // Reset a user's password
    void resetPassword(const std::string &username, const std::string &newPassword) {
        validateInput(username, newPassword);

        Database db;
        db.connect("host=localhost port=5432 dbname=yourdb user=youruser password=yourpass");

        auto user = db.fetchUserByUsername(username);
        if (user.empty()) {
            throw std::runtime_error("User does not exist");
        }

        std::string hashPassword = Crypto::hashPassword(newPassword);
        db.executeQuery("UPDATE users SET password = $1 WHERE username = $2", {hashPassword, username});

        std::cout << "Password reset successfully." << std::endl;
    }

    // Generate a secure token for password reset
    std::string generateResetToken(const std::string &username) {
        if (username.empty()) {
            throw std::invalid_argument("Username cannot be empty");
        }

        // Example token generation logic (use a secure method in production)
        std::string token = Crypto::hashPassword(username + std::to_string(std::time(nullptr)));

        std::cout << "Reset token generated: " << token << std::endl;
        return token;
    }

    // Validate a password reset token
    bool validateResetToken(const std::string &username, const std::string &token) {
        if (username.empty() || token.empty()) {
            throw std::invalid_argument("Username and token cannot be empty");
        }

        // Example validation logic (use a secure method in production)
        std::string expectedToken = Crypto::hashPassword(username + std::to_string(std::time(nullptr)));
        return token == expectedToken;
    }

private:
    // Common input validation logic
    void validateInput(const std::string &username, const std::string &password) {
        if (username.empty() || password.empty()) {
            throw std::invalid_argument("Username and password cannot be empty");
        }
    }
};



