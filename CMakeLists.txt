cmake_minimum_required(VERSION 3.15)
project(GovFileManagement)

set(CMAKE_CXX_STANDARD 17)

# Add all your source files here
add_executable(GovFileManagement
    src/main.cpp
    src/database.cpp
    src/auth.cpp
    src/crypto.cpp
    src/file_manager.cpp
    src/acl.cpp
    src/logger.cpp
)

# Find and link pqxx (requires vcpkg integration or toolchain file)
find_package(pqxx CONFIG REQUIRED)
target_link_libraries(GovFileManagement PRIVATE pqxx::pqxx)