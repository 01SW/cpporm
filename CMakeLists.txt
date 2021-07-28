cmake_minimum_required(VERSION 3.19)
project(cpporm)

set(CMAKE_CXX_STANDARD 14)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(BUILD_TEST OFF)

add_subdirectory(mysql)
add_subdirectory(sqlite)

add_library(SQLLib databoard.cpp)
target_link_libraries(SQLLib MySQLLib)
target_link_libraries(SQLLib SQLiteLib)

if(BUILD_TEST)
    message("build test")
    add_subdirectory(test)
endif()