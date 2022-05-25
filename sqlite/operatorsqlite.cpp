//
// Created by ws01 on 2021/7/24.
//

#include "operatorsqlite.h"

#include <iostream>

OperatorSQLite::OperatorSQLite(const std::string &db_path) {
    sqlite_ = nullptr;
    auto rc = sqlite3_open(db_path.c_str(), &sqlite_);
    if(rc != SQLITE_OK){
        std::string msg = "open sqlite3 fail";
        std::cout << msg << std::endl;
        throw std::runtime_error(msg);
    }
}

void OperatorSQLite::close() {
    if(sqlite_ != nullptr){
        sqlite3_close(sqlite_);
    }
}

bool OperatorSQLite::initSQL(const std::list<std::shared_ptr<TableBase>> &tableList) {
    auto end = tableList.end();
    for(auto it = tableList.begin(); it != end; ++it){
        auto table_name = (*it)->getTableName();
    }

    return true;
}

bool OperatorSQLite::getData(std::list<std::shared_ptr<TableBase>> &dataList, const std::shared_ptr<TableBase> &table,
                             const std::list<std::string> &condition, std::string *error) {
    return false;
}

bool OperatorSQLite::getCustomizeData(std::list<std::shared_ptr<TableBase>> &dataList,
                                      const std::shared_ptr<TableBase> &table, const std::string &condition,
                                      std::string *error) {
    return false;
}

bool OperatorSQLite::insertData(const std::shared_ptr<TableBase> &data, std::string *error, bool equal) {
    return false;
}

bool OperatorSQLite::modifyData(const std::shared_ptr<TableBase> &table, const std::list<std::string> &condition,
                                std::string *error) {
    return false;
}
