//
// Created by ws01 on 2021/7/23.
//

#include "operatormysql.h"

#include <iostream>
#include <stdexcept>
#include <vector>

OperatorMySQL::OperatorMySQL(const std::string &ip, int port, const std::string &user, const std::string &passwd,
                             const std::string &dbName) {
    mysql_init(&mysql_);
    if(!mysql_real_connect(&mysql_, ip.c_str(), user.c_str(), passwd.c_str(),
                           dbName.c_str(), port, nullptr, 0)){
        std::string msg = "mysql connect err";
        std::cout << msg << std::endl;
        throw std::runtime_error(msg);
    }
}

bool OperatorMySQL::initSQL(const std::list<std::shared_ptr<TableBase>> &tableList) {
    auto end = tableList.end();
    for(auto it = tableList.begin(); it != end; ++it){
        auto tableName = (*it)->getTableName();
        auto createSql = "create table if not exists " + tableName + " (";
        if((*it)->mapping.empty()){
            (*it)->initElement();
        }
        for(auto varIt = (*it)->mapping.begin(); varIt != (*it)->mapping.end(); ++varIt){
            if(varIt == (*it)->mapping.begin()){
                createSql += varIt->first;
            }else{
                createSql += ", " + varIt->first;
            }
            createSql += " ";

            switch(varIt->second.second){
                case TypeOfData::Bool:{
                    createSql += "BOOL ";
                    break;
                }
                case TypeOfData::Int:{
                    createSql += "INT ";
                    if((*it)->primaryKey == varIt->first && (*it)->selfIncreasing){
                        createSql += "AUTO_INCREMENT ";
                    }
                    break;
                }
                case TypeOfData::Double:{
                    createSql += "Double ";
                    break;
                }
                case TypeOfData::String:{
                    createSql += "Text ";
                    break;
                }
            }
            createSql += "NOT NULL";
        }

        if(!(*it)->primaryKey.empty()){
            createSql += ", PRIMARY KEY (" + (*it)->primaryKey + ")";
        }
        createSql += ")DEFAULT CHARSET=utf8mb4";

        if(mysql_query(&mysql_, createSql.c_str())){
            std::cout << "创建失败，sql语句:" << createSql << std::endl;
            return false;
        }
    }

    return true;
}

void OperatorMySQL::close() {
    mysql_close(&mysql_);
}

bool OperatorMySQL::getAllData(std::list<std::shared_ptr<TableBase>> &dataList,
                               const std::shared_ptr<TableBase> &tableName) {
    auto sql = "select * from " + tableName->getTableName();
    if(mysql_query(&mysql_, sql.c_str())){
        std::cout << "查询失败，失败语句:" << sql << std::endl;
        return false;
    }
    auto *res = mysql_store_result(&mysql_);
    if(res == nullptr){
        std::cout << "res == nullptr" << std::endl;
        return false;
    }
    MYSQL_ROW row = nullptr;
    MYSQL_FIELD *fd = nullptr;
    std::vector<MYSQL_FIELD*> fieldName;
    while ((fd = mysql_fetch_field(res))){
        fieldName.emplace_back(fd);
    }
    auto c = fieldName.size();
    while ((row = mysql_fetch_row(res))){
        auto data = tableName->makePtr();

        for(int i = 0; i < c; i++){
            std::string sqlData(row[i]);
            auto pair = data->mapping[fieldName[i]->name];
            switch(pair.second){
                case TypeOfData::Bool:{
                    *(bool*)pair.first = std::strtol(sqlData.c_str(), nullptr, 10);
                    break;
                }
                case TypeOfData::Int:{
                    *(int*)pair.first = static_cast<int>(std::strtol(sqlData.c_str(), nullptr, 10));
                    break;
                }
                case TypeOfData::Double:{
                    *(double*)pair.first = std::strtod(sqlData.c_str(), nullptr);
                    break;
                }
                case TypeOfData::String:{
                    *(std::string*)pair.first = sqlData;
                    break;
                }
            }
        }
        dataList.emplace_back(data);
    }

    mysql_free_result(res);
    return true;
}
