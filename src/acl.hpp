//- Access control logic for checking, assigning, and revoking permissions.


#ifndef ACL_HPP
#define ACL_HPP
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>
#include <set>


class ACL {
    public:
        // Add a user to the ACL with specific permissions
        void addUser(const std::string &username, const std::set<std::string> &permissions) {
            if (permissions.empty()) {
                throw std::invalid_argument("Permissions cannot be empty.");
            }
            acl_[username] = permissions;
        }

    
        std::unordered_map<std::string, std::set<std::string>> acl_;

        // Remove a user from the ACL
        void removeUser(const std::string &username) {
            auto it = acl_.find(username);
            if (it != acl_.end()) {
                acl_.erase(it);
            } else {
                throw std::runtime_error("User not found in ACL.");
            }
        }

        // Check if a user has a specific permission
        bool hasPermission(const std::string &username, const std::string &permission) const {
            auto it = acl_.find(username);
            if (it != acl_.end()) {
                return it->second.find(permission) != it->second.end();
            }
            return false;
        }

        // List all users and their permissions
        void listUsers() const {
            for (const auto &entry : acl_) {
                std::cout << "User: " << entry.first << ", Permissions: ";
                for (const auto &perm : entry.second) {
                    std::cout << perm << " ";
                }
                std::cout << std::endl;
            }
        }

};

#endif // ACL_HPP