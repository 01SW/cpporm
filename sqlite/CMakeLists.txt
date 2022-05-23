aux_source_directory(. SQLiteSource)

find_package(Threads REQUIRED)

add_library(SQLiteLib ${SQLiteSource})
target_link_libraries(SQLiteLib ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(SQLiteLib dl)