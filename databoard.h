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
    bool getAllData(std::list<std::shared_ptr<TableBase>> &dataList,
                    const std::shared_ptr<TableBase> &tableName, std::string *error = nullptr); ///< 获取一个表的全部数据
    /**
     * @brief 获取数据
     * @details 获取符合条件的数据，使用时先在table中为数据设置想要的值然后在condition中将值的名称添加进来
     * @param dataList 结果，符合所有条件的并集
     * @param table 表名与条件值
     * @param condition 条件，所填写的值为变量名，当条件为空时则表示无条件的获取全部数据
     * @param error 发生错误时的原因，当不需要知道原因时可不填
     * @return 是否获取成功
     * @note 当返回成功时表示获取成功，但是此时可能不存在数据
     */
    bool getData(std::list<std::shared_ptr<TableBase>> &dataList, const std::shared_ptr<TableBase> &table,
                 const std::list<std::string> &condition, std::string *error = nullptr);
    /**
     * @brief 获取数据
     * @details 获取符合条件的数据，与getData函数功能类似。不过获取条件将有用户指定，需要用户填充部分的sql语句。
     * @param dataList 符合条件的结果
     * @param table 表名
     * @param condition 条件，为所需要填充的sql语句，举例:"age >= 19 and name = 'abcd'"
     * @param error 发生错误时的原因，当不需要知道原因时可不填
     * @return 是否获取成功
     * @note 当返回成功时表示获取成功，但是此时可能不存在数据
     * @warning 所填充的sql语句根据不同类型的数据库而不同，不具备通用性。切换数据库时需要注意
     */
    bool getCustomizeData(std::list<std::shared_ptr<TableBase>> &dataList, const std::shared_ptr<TableBase> &table,
                          const std::string &condition, std::string *error = nullptr);
    bool getPrimaryKeyData(std::shared_ptr<TableBase> &data, std::string *error = nullptr); ///< 根据主键获取数据

    /**
     * @brief 插入数据
     * @details 将新数据插入到数据库中
     * @param data 新数据
     * @param err 发生错误时的原因，当不需要知道原因时可不填
     * @param equal 强制使用data中存在的主键，仅当该数据表存在主键且主键为自增的Int类型时起效
     * @return 是否插入成功
     * @note 当该数据表存在主键且主键为自增的Int类型时默认将使用主键自增，若想强制设置主键请设置equal为true
     */
    bool insertData(const std::shared_ptr<TableBase> &data, std::string *err = nullptr, bool equal = false);

    /**
     * @brief 修改数据
     * @details 根据指定条件查询数据，若数据存在则将其进行修改
     * @param table 新数据
     * @param condition 条件
     * @param error 若修改失败时的错误原因
     * @return 是否修改成功
     */
    bool modifyData(const std::shared_ptr<TableBase> &table, const std::list<std::string> &condition,
                    std::string *error = nullptr);

protected:
    SQLType sqlType_;
    std::shared_ptr<SQLBase> sqlPtr_;
};


#endif //CPPORM_DATABOARD_H
