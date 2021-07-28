//
// Created by ws01 on 2021/7/23.
//

#include "databoard.h"
#include "mysql/operatormysql.h"

#include <exception>

DataBoard::DataBoard(SQLType type, const std::shared_ptr<SQLBase> &sqlPtr) {
    sqlType_ = type;
    sqlPtr_ = sqlPtr;
}

DataBoard::DataBoard(const std::string &ip, int port, const std::string &user, const std::string &password,
                     const std::string &dbName) {
    sqlType_ = SQLType::MySQL;
    try {
        sqlPtr_ = std::make_shared<OperatorMySQL>(ip, port, user, password, dbName);
    } catch (const std::exception &ep){
        throw ep;
    }
}

DataBoard::~DataBoard() {
    if(sqlPtr_.use_count() != 0){
        sqlPtr_->close();
    }
}

bool DataBoard::initData(const std::list<std::shared_ptr<TableBase>> &tableList) {
    return sqlPtr_->initSQL(tableList);
}

bool
DataBoard::getAllData(std::list<std::shared_ptr<TableBase>> &dataList, const std::shared_ptr<TableBase> &tableName) {
    return sqlPtr_->getAllData(dataList, tableName);
}
