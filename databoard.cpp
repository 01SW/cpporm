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
DataBoard::getAllData(std::list<std::shared_ptr<TableBase>> &dataList,
                      const std::shared_ptr<TableBase> &tableName, std::string *error) {
    return sqlPtr_->getCustomizeData(dataList, tableName, "", error);
}

bool DataBoard::getData(std::list<std::shared_ptr<TableBase>> &dataList, const std::shared_ptr<TableBase> &table,
                        const std::list<std::string> &condition, std::string *error) {
    return sqlPtr_->getData(dataList, table, condition, error);
}

bool DataBoard::getPrimaryKeyData(std::shared_ptr<TableBase> &data, std::string *error) {
    if(data->primaryKey.empty()){
        if(error != nullptr){
            *error = "primaryKey nullptr";
        }
        return false;
    }
    std::list<std::shared_ptr<TableBase>> dataList;
    std::list<std::string> condition;
    condition.emplace_back(data->primaryKey);

    auto result = sqlPtr_->getData(dataList, data, condition, error);
    if(result){
        if(!dataList.empty()){
            data.swap(dataList.front());
        }
    }

    return result;
}

bool
DataBoard::getCustomizeData(std::list<std::shared_ptr<TableBase>> &dataList, const std::shared_ptr<TableBase> &table,
                            const std::string &condition, std::string *error) {
    return sqlPtr_->getCustomizeData(dataList, table, condition, error);
}

bool DataBoard::insertData(const std::shared_ptr<TableBase> &data, std::string *err, bool equal) {
    return sqlPtr_->insertData(data, err, equal);
}
