// acl.cpp / acl.hpp
//- Access control logic for checking, assigning, and revoking permissions.

#include "acl.hpp"
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <set>
#include <string>
#include <algorithm>
#include <memory>
#include <vector>
#include <stdexcept>
#include <iostream>
#include "file_manager.hpp"
#include "crypto.hpp"

std::unordered_map<std::string, std::set<std::string>> acl_;

class ACL {
    public:
    // add user to the ACL(Access Control List) with specific permissions
    void addUser(const std::string &username, const std::set<std::string> &permissions){
        if (permissions.empty()){
            throw std::invalid_argument("Permissions cannot be empty.");
        }
        // if the user exists, their permissions are updated to the new set provided
             

        acl_[username] = permissions;
        if (acl_.find(username) !=acl_.end()) {
            acl_[username].insert(permissions.begin(), permissions.end());
        } else {
            acl_[username] = permissions;
        }
        
    }
    void removeUser(const std::string &username){
        auto it = acl_.find(username);
        //remove  the user and their permissions for the ACL
        if(acl_.find(username)!= acl_.end()){
            acl_.erase(it);
        } else {
            throw std::runtime_error("User not found in ACL.");
        }

    }
    void listUsers() const {
        //print all users in the access control list along with their permissions
        for (const auto &entry : acl_) {
            std:: cout << "User: " << entry.first << ", Permissions: ";
            for (const auto &perm : entry.second) {
                std::cout << perm << " ";
            }
        }
        //potentially add debug statements to see what users and permissions are being processed
        std::cout << std::endl;
        
    }
    bool hasPermission(const std::string &username, const std::string &permission) const {
        //check if a user has a specific permission
        auto it = acl_.find(username);
        if(it != acl_.end()) {
            return it->second.find(permission) != it->second.end();//return true

        }
        return false;
    }
};

