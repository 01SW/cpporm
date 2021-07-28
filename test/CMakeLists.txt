cmake_minimum_required(VERSION 3.19)
project(cppormtest)

set(CMAKE_CXX_STANDARD 14)

set(MYSQL_LIBS
        mysqlclient.a pthread z.a m rt.a atomic.a ssl.a crypto.a dl
        )

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../lib/libSQLLib.a)
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../lib/libMySQLLib.a)
target_link_libraries(${PROJECT_NAME} ${MYSQL_LIBS})