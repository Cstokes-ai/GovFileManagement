/*
Purpose:
Establish connection to PostgreSQL and implement safe query execution functions.


Tasks:

Connect to PostgreSQL using pqxx or libpq.

Write generic functions like execute_query(), fetch_user_by_username(), insert_log_entry(), etc.

Handle parameterized queries (to prevent SQL injection).
*/

#include <pqxx/pqxx>
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <memory>
