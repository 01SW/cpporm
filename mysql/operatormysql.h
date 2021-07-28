//
// Created by ws01 on 2021/7/23.
//

#ifndef CPPORM_OPERATORMYSQL_H
#define CPPORM_OPERATORMYSQL_H

#include "../sqlBase/sqlbase.h"

#include <mysql/mysql.h>

class OperatorMySQL : public SQLBase {
public:
    explicit OperatorMySQL(const std::string &ip, int port, const std::string &user,
                           const std::string &passwd, const std::string &dbName);

    void close() override;
    bool initSQL(const std::list<std::shared_ptr<TableBase>> &tableList) override;

    bool getAllData(std::list<std::shared_ptr<TableBase>> &dataList,
                    const std::shared_ptr<TableBase> &tableName) override;

private:
    MYSQL mysql_;
};


#endif //CPPORM_OPERATORMYSQL_H
