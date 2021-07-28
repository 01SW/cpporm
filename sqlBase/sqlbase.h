//
// Created by ws01 on 2021/7/27.
//

#ifndef CPPORM_SQLBASE_H
#define CPPORM_SQLBASE_H

#include "../tablebase.h"

class SQLBase {
public:
    virtual void close() = 0; ///< 与数据库断开连接
    /**
     * @brief 初始化数据库
     * @details 对数据库做初始化操作，若成功则会使数据库存在与结构体等价的表
     * @param tableList 表集合
     * @return 是否成功
     */
    virtual bool initSQL(const std::list<std::shared_ptr<TableBase>> &tableList) = 0; //TODO 暂不支持修改数据表

    virtual bool getAllData(std::list<std::shared_ptr<TableBase>> &dataList,
                            const std::shared_ptr<TableBase> &tableName) = 0; ///< 获取一个表的全部数据
};

#endif //CPPORM_SQLBASE_H
