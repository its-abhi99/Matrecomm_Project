cmake_minimum_required(VERSION 3.10)
project(yugabyte_connector)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set Poco paths explicitly
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "/usr/local")
set(POCO_PREFIX_PATH "/usr/local")
set(POCO_INCLUDE_PATH "${POCO_PREFIX_PATH}/include")
set(POCO_LIB_PATH "${POCO_PREFIX_PATH}/lib")

# Find PostgreSQL
find_package(PostgreSQL REQUIRED)

# Find Poco components
find_package(Poco REQUIRED COMPONENTS Foundation Data)

# Create the connector library
add_library(yugabyte_connector STATIC
    src/YBConnection.cpp
    src/YBQuery.cpp
    src/YBResult.cpp
    src/YBError.cpp
    src/YBAuthentication.cpp
    src/EmployeeManagement.cpp  # Added new source file
)

# Set include directories
target_include_directories(yugabyte_connector
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${Poco_INCLUDE_DIRS}
    ${PostgreSQL_INCLUDE_DIRS}
    ${POCO_INCLUDE_PATH}
)

# Link libraries
target_link_directories(yugabyte_connector
    PRIVATE
    ${POCO_LIB_PATH}
)

target_link_libraries(yugabyte_connector
    PRIVATE
    Poco::Foundation
    Poco::Data
    PocoDataPostgreSQL
    PostgreSQL::PostgreSQL
)

# Create test executable for main_test.cpp
add_executable(main_test
    tests/main_test.cpp
)

# Link the test executable for main_test
target_link_libraries(main_test
    PRIVATE
    yugabyte_connector
)

# Create test executable for employee_management_test.cpp
add_executable(employee_management_test
    tests/employee_management_test.cpp
)

# Link the test executable for employee_management_test
target_link_libraries(employee_management_test
    PRIVATE
    yugabyte_connector
)


# Print some debug information
message(STATUS "Poco Include Dirs: ${Poco_INCLUDE_DIRS}")
message(STATUS "Poco Libraries: ${Poco_LIBRARIES}")
message(STATUS "PostgreSQL Include Dirs: ${PostgreSQL_INCLUDE_DIRS}")
message(STATUS "PostgreSQL Libraries: ${PostgreSQL_LIBRARIES}")
