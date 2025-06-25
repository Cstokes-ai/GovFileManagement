cmake_minimum_required(VERSION 3.14)
project(GovFileManagement)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Tell CMake where to find Qt 6
set(CMAKE_PREFIX_PATH "C:/Qt/6.9.1/mingw_64/lib/cmake")

# Find Qt6 Widgets module
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Find libpqxx (PostgreSQL C++ client library)
find_package(PQXX REQUIRED)

# Add your source files
add_executable(GovFileManagement
    main.cpp
    file_manager.cpp
    login.cpp
    database.cpp
    acl.cpp
    crypto.cpp
    auth.cpp
    # Add more .cpp files here if needed
)

# Link against Qt6 and libpqxx
target_link_libraries(GovFileManagement
    PRIVATE
        Qt6::Widgets
        PQXX::pqxx
)
