#ifndef SQLSERVICE_H
#define SQLSERVICE_H


#include <QSqlDatabase>
#include <QSqlError>

#include "user.h"
#include "task.h"


class SqlService
{
    static QSqlDatabase dataBase;

public:
    static void Connect();

    static void AddUser(QString name, QString password);

    static void AddTask(User currentUser, Task task);
    static void DeleteTask(User currentUser, Task task);

    static void GetUser(QString userName,QString userPassword);

private:
    static bool CheckUserExists(QString userName,QString userPassword);
    static bool CheckTaskExists(QString taskHeader);
};

#endif // SQLSERVICE_H
