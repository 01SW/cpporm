//
// Created by ws01 on 2021/7/23.
//

#ifndef ZEROMUSICSERVICE_SQLBASE_H
#define ZEROMUSICSERVICE_SQLBASE_H

#include <memory>
#include <string>
#include <list>
#include <map>

#define MAKE_TABLE_PTR(Name) std::shared_ptr<TableBase> makePtr() override{ \
                                        auto ptr = std::make_shared<Name>(); \
                                        ptr->initElement();               \
                                        return ptr;                   \
                                        }                                 \
                            std::string getTableName() const override{ \
                                        return #Name;             \
                                        }

enum class TypeOfData:char{Bool, Int, Double, String};

/**
 * @brief 数据表结构体
 * @details 与数据表相等价，用于创建、获取、修改数据表的中介，使用时继承此结构体添加对应元素并完成相关纯虚函数，无特殊要求时可添加上述宏定义。
 */
struct TableBase{

    virtual void initElement() = 0; ///< 用于完成结构体内元素指针与名称的映射
    virtual std::shared_ptr<TableBase> makePtr() = 0; ///< 用于创建一个与自身相同类型的新对象，请调用新对象的initElement函数
    virtual std::string getTableName() const = 0; ///< 获取表名

    std::map<std::string, std::pair<void*, TypeOfData>> mapping;
    std::string primaryKey; ///< 主键，若不设则请留空
    bool selfIncreasing = false; ///< 自增，当设置了主键且主键为int类型时生效
};

#endif //ZEROMUSICSERVICE_SQLBASE_H
