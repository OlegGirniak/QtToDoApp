#include "sqlservice.h"

QSqlDatabase SqlService::dataBase = QSqlDatabase::addDatabase("QSQLITE");


void SqlService::Connect()
{
    dataBase.setDatabaseName("todolist.db");
    if(dataBase.open()){

    }
}
