//
// Created by ws01 on 2021/7/28.
//

#ifndef CPPORM_TABLE_H
#define CPPORM_TABLE_H

#include "../tablebase.h"

struct Test1 : public TableBase{
    int a = 0;
    double b = 0;
    short c = 0;
    std::string d;
    std::string e;

    void initElement() override{
        mapping.clear();
        mapping.insert(std::make_pair("a", std::make_pair(&a, TypeOfData::Int)));
        mapping.insert(std::make_pair("b", std::make_pair(&b, TypeOfData::Double)));
        mapping.insert(std::make_pair("c", std::make_pair(&c, TypeOfData::Bool)));
        mapping.insert(std::make_pair("d", std::make_pair(&d, TypeOfData::String)));
        mapping.insert(std::make_pair("e", std::make_pair(&e, TypeOfData::String)));

        primaryKey = "a";
        selfIncreasing = true;
    }

    MAKE_TABLE_PTR(Test1)
};

#endif //CPPORM_TABLE_H
