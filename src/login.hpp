// this file hanndles the login functionality of the application


#ifndef LOGIN_HPP
#define LOGIN_HPP
#include <string>
#include <stdexcept>
#include <iostream>
#include <unordered_map>
#include <memory>
#include <set>


class Login {
    public:
    void registerUser(const std::string &username, const std::string &password);
    bool loginUser(const std::string &username, const std::string &password);
    void logoutUser(const std::string &username);

};
std::unordered_map<std::string, std::string> userDatabase_; // Stores username and hashed password
std::unordered_map<std::string, bool> userSessions_; // Stores username and login status

#endif // LOGIN_HPP