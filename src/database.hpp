/*
Purpose:
Establish connection to PostgreSQL and implement safe query execution functions.


Tasks:

Connect to PostgreSQL using pqxx or libpq.

Write generic functions like execute_query(), fetch_user_by_username(), insert_log_entry(), etc.

Handle parameterized queries (to prevent SQL injection).
*/

#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <pqxx/pqxx>
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <memory>

class Database {
public:
    // Establish connection to the PostgreSQL database
    void connect(const std::string& connectionString);

    // Execute a generic SQL query (INSERT, UPDATE, DELETE, etc.)
    void executeQuery(const std::string& query, const std::vector<std::string>& params = {});

    // Fetch user information by username (returns user data as a vector or struct)
    std::vector<std::string> fetchUserByUsername(const std::string& username);

    // Insert a log entry into the logs table
    void insertLogEntry(const std::string& message, const std::string& username);

    // (Optional) Close the database connection
    void close();

private:
    std::unique_ptr<pqxx::connection> conn_;
};

#endif // DATABASE_HPP
