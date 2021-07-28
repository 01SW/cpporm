cmake_minimum_required(VERSION 3.19)
project(cpporm)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(mysql)
add_subdirectory(sqlite)

add_library(SQLLib databoard.cpp)
target_link_libraries(SQLLib MySQLLib)
target_link_libraries(SQLLib SQLiteLib)