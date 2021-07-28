aux_source_directory(. SQLiteSource)

add_library(SQLiteLib ${SQLiteSource})
target_link_libraries(SQLiteLib sqlite3)