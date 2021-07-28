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
    auto password = "root";
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

        //获取表中所有数据
        for(auto &table : list){
            std::list<std::shared_ptr<TableBase>> data;
            dataBoard->getAllData(data, table);
            for(auto &it : data){
                auto ptr = std::dynamic_pointer_cast<Test1>(it);
                std::cout << ptr->a << " " << ptr->b << " " << ptr->c << " " << ptr->d << " " << ptr->e << std::endl;
            }
        }
    }catch (const std::exception &ep){
        std::cout << ep.what() << std::endl;
    }
}