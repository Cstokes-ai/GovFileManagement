//Login file. this must connect with the database and other files to handle user login and registration
#include "login.hpp"
#include "database.hpp" // Add this include
#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include <string>
#include <memory>
#include <set>
#include "crypto.hpp"
#include "file_manager.hpp"
#include "acl.hpp"

// Remove the class definition here; implement methods from login.hpp instead

// Example: create a Database object and connect in your Login class constructor
Login::Login() {
    db_.connect("host=localhost port=5432 dbname=yourdb user=youruser password=yourpass");
}

// Example: use db_ in registerUser
void Login::registerUser(const std::string &username, const std::string &password) {
    if (username.empty() || password.empty()) {
        throw std::invalid_argument("Username and password cannot be empty.");
    }
    // Check if user exists in the database
    auto user = db_.fetchUserByUsername(username);
    if (!user.empty()) {
        throw std::runtime_error("Username already exists.");
    }
    std::string hashPassword = Crypto::hashPassword(password);
    // Insert new user into the database (example query)
    db_.executeQuery("INSERT INTO users (username, password) VALUES ($1, $2)", {username, hashPassword});
}

// ...implement other Login methods using db_ as needed...
