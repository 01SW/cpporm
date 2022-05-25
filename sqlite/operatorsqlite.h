//
// Created by ws01 on 2021/7/24.
//

#ifndef CPPORM_OPERATORSQLITE_H
#define CPPORM_OPERATORSQLITE_H

#include "../sqlBase/sqlbase.h"

#include "sqlite3.h"

class OperatorSQLite : public SQLBase{
public:
    explicit OperatorSQLite(const std::string &db_path);

    void close() override;
    bool initSQL(const std::list<std::shared_ptr<TableBase>> &tableList) override;

    bool getData(std::list<std::shared_ptr<TableBase>> &dataList, const std::shared_ptr<TableBase> &table,
                 const std::list<std::string> &condition, std::string *error) override;
    bool getCustomizeData(std::list<std::shared_ptr<TableBase>> &dataList,
                          const std::shared_ptr<TableBase> &table, const std::string &condition,
                          std::string *error) override;

    bool insertData(const std::shared_ptr<TableBase> &data, std::string *error, bool equal) override;

    bool modifyData(const std::shared_ptr<TableBase> &table, const std::list<std::string> &condition,
                    std::string *error) override;

private:
    sqlite3 *sqlite_;
};


#endif //CPPORM_OPERATORSQLITE_H
