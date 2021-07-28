//
// Created by ws01 on 2021/7/23.
//

#ifndef CPPORM_DATABOARD_H
#define CPPORM_DATABOARD_H

#include <memory>
#include <list>

class SQLBase;
struct TableBase;

enum class SQLType:char{MySQL, SQLite};

class DataBoard {
public:
    explicit DataBoard(SQLType type, const std::shared_ptr<SQLBase> &sqlPtr);
    explicit DataBoard(const std::string &ip, int port, const std::string &user, const std::string &password, const std::string &dbName); ///< mysql
    ~DataBoard();

    bool initData(const std::list<std::shared_ptr<TableBase>> &tableList); ///< 初始化程序数据
    bool getAllData(std::list<std::shared_ptr<TableBase>> &dataList, const std::shared_ptr<TableBase> &tableName); ///< 获取一个表的全部数据

protected:
    SQLType sqlType_;
    std::shared_ptr<SQLBase> sqlPtr_;
};


#endif //CPPORM_DATABOARD_H
