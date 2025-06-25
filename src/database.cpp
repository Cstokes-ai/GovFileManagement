#include <iostream>
#include "database.hpp"
#include <pqxx/pqxx>
#include <stdexcept>
#include <vector>
#include <string>
#include <memory>
#include <pqxx/transaction>




class Database {
public:
    // Establish connection to the PostgreSQL database
    void connect(const std::string& connectionString) {
        try {
            conn_ = std::make_unique<pqxx::connection>(connectionString);
            if (!conn_ || !conn_->is_open()) {
                throw std::runtime_error("Failed to open database connection");
            }
        } catch (const std::exception& e) {
            std::cerr << "Database connection error: " << e.what() << std::endl;
            throw;
        }
    }

    // Execute a generic SQL query (INSERT, UPDATE, DELETE, etc.)
    void executeQuery(const std::string& query, const std::vector<std::string>& params = {}) {
        if (!conn_ || !conn_->is_open()) {
            throw std::runtime_error("Database connection is not open");
        }
        pqxx::work txn(*conn_);
        try {
            txn.exec_params(query, params);
            txn.commit();
        } catch (const pqxx::sql_error& e) {
            std::cerr << "SQL error: " << e.what() << " Query: " << e.query() << std::endl;
            throw;
        } catch (const std::exception& e) {
            std::cerr << "Error executing query: " << e.what() << std::endl;
            throw;
        }
    }

    // Fetch user information by username
    std::vector<std::string> fetchUserByUsername(const std::string& username) {
        pqxx::work txn(*conn_);
        try {
            pqxx::result res = txn.exec_params("SELECT * FROM users WHERE username = $1", username);
            if (res.empty()) {
                return {}; // No user found
            }
            // Assuming the first column is the username and the second is the email
            return {res[0][0].as<std::string>(), res[0][1].as<std::string>()};
        } catch (const pqxx::sql_error& e) {
            std::cerr << "SQL error: " << e.what() << " Query: " << e.query() << std::endl;
            throw;
        } catch (const std::exception& e) {
            std::cerr << "Error fetching user: " << e.what() << std::endl;
            throw;
        }
    }

    // Insert a log entry into the logs table
    void insertLogEntry(const std::string& message, const std::string& username) {
        pqxx::work txn(*conn_);
        try {
            txn.exec_params("INSERT INTO logs (message, username) VALUES ($1, $2)", message, username);
            txn.commit();
        } catch (const pqxx::sql_error& e) {
            std::cerr << "SQL error: " << e.what() << " Query: " << e.query() << std::endl;
            throw;
        } catch (const std::exception& e) {
            std::cerr << "Error inserting log entry: " << e.what() << std::endl;
            throw;
        }
    }

private:
    std::unique_ptr<pqxx::connection> conn_;
};