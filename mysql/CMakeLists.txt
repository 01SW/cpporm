aux_source_directory(. MySQLSource)

add_library(MySQLLib ${MySQLSource})
set(MYSQL_LIBS
        mysqlclient.a pthread z.a m rt.a atomic.a ssl.a crypto.a dl
        )
target_link_libraries(MySQLLib ${MYSQL_LIBS})