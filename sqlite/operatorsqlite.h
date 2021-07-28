//
// Created by ws01 on 2021/7/24.
//

#ifndef ZEROMUSICSERVICE_OPERATORSQLITE_H
#define ZEROMUSICSERVICE_OPERATORSQLITE_H

#include "../sqlBase/sqlbase.h"

#include <sqlite3.h>

class OperatorSQLite : public SQLBase{
private:
    sqlite3 *sqlite_;
};


#endif //ZEROMUSICSERVICE_OPERATORSQLITE_H
