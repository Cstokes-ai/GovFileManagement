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

    //register a new user
    void registerUser(const std::string &username, const std::string &password){
        // Check if username and password are not empty
        if (username.empty() || password.empty()) {
            throw std::invalid_argument("Username and password is empty");

        }
        //check if the user is in the database already
        Database db;
        db.connect("host=localhost port=5432 dbname=yourdb user=youruser password=yourpass");
        auto user = db.fetchUserByUsername(username);
        if(!user.empty()){
            throw std::runtime_error("Username already exists");
        }
        //hash the password
        std::string hashPassword = Crypto::hashPassword(password);
        //store into database
        db.executeQuery("INSERT INTO users (username, password) VALUES ($1, $2)", {username, hashPassword});    
        


    }
    //authenticate a user
    bool authenticateUser(const std::string &username, const std::string &password);
};