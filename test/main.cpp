//
// Created by ws01 on 2021/7/28.
//

#include "../databoard.h"
#include "table.h"

#include <iostream>

void testMySQL();

int main(){
    testMySQL();

    return 0;
}

void testMySQL(){
    auto ip = "127.0.0.1";
    auto port = 3306;
    auto user = "root";
    auto password = "123456";
    auto dbName = "zeroMusic";
    try {
        auto dataBoard = std::make_shared<DataBoard>(ip, port, user, password, dbName);

        std::list<std::shared_ptr<TableBase>> list;
        list.push_back(std::make_shared<Test1>());

        //初始化
        if(!dataBoard->initData(list)){
            std::cout << "初始化失败" << std::endl;
            return;
        }

        //插入数据
        {
            std::cout << "插入数据:" << std::endl;
            auto data = std::make_shared<Test1>();
            data->initElement();
            data->b = 3;
            data->c = 1;
            data->d = "abcd";
            data->e = "xxx";

            std::string error;
            if(!dataBoard->insertData(data, &error)){
                std::cout << "插入数据失败，原因:" << error << std::endl;
            }else{
                std::cout << "数据插入成功" << std::endl;
            }
        }

        //获取部分数据
        {
            std::cout << "获取部分数据:" << std::endl;
            auto testPtr = std::make_shared<Test1>();
            testPtr->initElement();
            std::list<std::shared_ptr<TableBase>> data;
            testPtr->c = 1;
            testPtr->d = "b";
            std::list<std::string> condition;
            condition.emplace_back("c");
            condition.emplace_back("d");
            std::string error;
            if(!dataBoard->getData(data, testPtr, condition, &error)){
                std::cout << "获取失败，原因:" << error << std::endl;
                return;
            }
            for(auto &it : data){
                auto ptr = std::dynamic_pointer_cast<Test1>(it);
                std::cout << ptr->a << " " << ptr->b << " " << ptr->c << " " << ptr->d << " " << ptr->e << std::endl;
            }
        }

        //获取表中所有数据
        std::cout << "全部数据:" << std::endl;
        for(auto &table : list){
            std::list<std::shared_ptr<TableBase>> data;
            std::string error;
            if(!dataBoard->getAllData(data, table, &error)){
                std::cout << "获取:" << table->getTableName() << "表失败，原因:" << error << std::endl;
            }
            for(auto &it : data){
                auto ptr = std::dynamic_pointer_cast<Test1>(it);
                std::cout << ptr->a << " " << ptr->b << " " << ptr->c << " " << ptr->d << " " << ptr->e << std::endl;
            }
        }
    }catch (const std::exception &ep){
        std::cout << ep.what() << std::endl;
    }
}