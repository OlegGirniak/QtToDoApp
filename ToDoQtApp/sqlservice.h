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

    static void UpdateTask(QString header, QString description);

    static void DeleteTask(int currentUserId, QString taskHeader);

    static User GetUser(QString userName,QString userPassword);

    static void GetUserTasks(User& user);

    static bool CheckUserExists(QString userName);

    static bool CheckTaskExists(QString taskHeader);

    static int GetTaskIdByHeader(QString header);

};

#endif // SQLSERVICE_H
