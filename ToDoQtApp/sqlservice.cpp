#include "sqlservice.h"
#include "qsqlquery.h"
#include <QDebug>

QSqlDatabase SqlService::dataBase = QSqlDatabase::addDatabase("QSQLITE");

void SqlService::Connect()
{
    dataBase.setDatabaseName("todolist.db");
    if(!dataBase.open()){
         qDebug() << "Error connecting";
    }
}

void SqlService::AddUser(QString name, QString password)
{
    if (!dataBase.isOpen())
    {
        qDebug() << "Database is not open!";
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO users (name, password) VALUES (:name, :password)");
    query.bindValue(":name", name);
    query.bindValue(":password", password);

    if (!query.exec())
    {
        qDebug() << "Error executing query:" << query.lastError().text();
        return;
    }

    qDebug() << "User added successfully";
}

void SqlService::AddTask(User currentUser, Task task)
{
    if (!dataBase.isOpen())
    {
        qDebug() << "Database is not open!";
        return;
    }

    // Додаємо нове завдання до таблиці tasks
    QSqlQuery taskQuery;
    taskQuery.prepare("INSERT INTO tasks (header, description) VALUES (:header, :description)");
    taskQuery.bindValue(":header", task.GetHeader());
    taskQuery.bindValue(":description", task.GetDescription());

    if (!taskQuery.exec())
    {
        qDebug() << "Error executing query:" << taskQuery.lastError().text();
        return;
    }

    // Отримуємо ідентифікатор доданого завдання
    int taskId = taskQuery.lastInsertId().toInt();

    // Вставляємо запис до таблиці users_tasks
    QSqlQuery userTaskQuery;
    userTaskQuery.prepare("INSERT INTO users_tasks (id_user, id_task) VALUES (:userId, :taskId)");
    userTaskQuery.bindValue(":userId", currentUser.GetId());
    userTaskQuery.bindValue(":taskId", taskId);

    if (!userTaskQuery.exec())
    {
        qDebug() << "Error executing query:" << userTaskQuery.lastError().text();
        return;
    }

    qDebug() << "Task added successfully";
}

void SqlService::UpdateTask(QString header, QString description)
{
    if (!dataBase.isOpen())
    {
        qDebug() << "Database is not open!";
        return;
    }

    QSqlQuery query;
    query.prepare("UPDATE tasks SET description = :description WHERE header = :header");
    query.bindValue(":description", description);
    query.bindValue(":header", header);

    if (!query.exec())
    {
        qDebug() << "Error executing query:" << query.lastError().text();
        return;
    }

    qDebug() << "Task updated successfully";
}

void SqlService::DeleteTask(int currentUserId, QString taskHeader)
{
    int taskId = SqlService::GetTaskIdByHeader(taskHeader);
    if(taskId != -1){

        QSqlQuery userTaskQuery;
        userTaskQuery.prepare("DELETE FROM users_tasks WHERE id_task = :taskId");
        userTaskQuery.bindValue(":taskId", taskId);

        qDebug() << userTaskQuery.executedQuery();

        if (!userTaskQuery.exec())
        {
            qDebug() << "Error executing query:" << userTaskQuery.lastError().text();
            return;
        }

        // Видалення запису з таблиці tasks
        QSqlQuery taskQuery;
        taskQuery.prepare("DELETE FROM tasks WHERE id = :taskId");
        taskQuery.bindValue(":taskId", taskId);

        if (!taskQuery.exec())
        {
            qDebug() << "Error executing query:" << taskQuery.lastError().text();
            return;
        }

        qDebug() << "Task deleted successfully";
    }
}


User SqlService::GetUser(QString userName, QString userPassword)
{
    User user;

    if (!dataBase.isOpen())
    {
        qDebug() << "Database is not open!";
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE name = :userName AND password = :userPassword");
    query.bindValue(":userName", userName);
    query.bindValue(":userPassword", userPassword);

    if (!query.exec())
    {
        qDebug() << "Error executing query:" << query.lastError().text();
        return user;
    }


    if (query.next())
    {
        user.SetId(query.value("id").toInt());
        user.SetName(query.value("name").toString());
        user.SetPassword(query.value("password").toString());
    }

    GetUserTasks(user);

    return user;
}

void SqlService::GetUserTasks(User &user)
{
    if (!dataBase.isOpen())
    {
        qDebug() << "Database is not open!";
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT id_task FROM users_tasks WHERE id_user = :userId");
    query.bindValue(":userId", user.GetId());

    if (!query.exec())
    {
        qDebug() << "Error executing query:" << query.lastError().text();
        return;
    }

    QList<Task> tasks;

    while (query.next())
    {
        int taskId = query.value(0).toInt();

        QSqlQuery taskQuery;
        taskQuery.prepare("SELECT * FROM tasks WHERE id = :taskId");
        taskQuery.bindValue(":taskId", taskId);
        if (!taskQuery.exec())
        {
            qDebug() << "Error executing query:" << taskQuery.lastError().text();
            continue;
        }

        if (taskQuery.next())
        {
            Task task(taskQuery.value("header").toString(), taskQuery.value("description").toString());
            tasks.append(task);
        }
    }

    user.SetTasks(tasks);
}

bool SqlService::CheckUserExists(QString userName)
{
    if (!dataBase.isOpen())
    {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM users WHERE name = :userName");
    query.bindValue(":userName", userName);


    if (!query.exec())
    {
        qDebug() << "Error executing query:" << query.lastError().text();
        return false;
    }

    query.next();
    return query.value(0).toInt() > 0;
}

int SqlService::GetTaskIdByHeader(QString header)
{
    if (!dataBase.isOpen())
    {
        qDebug() << "Database is not open!";
        return -1;
    }

    QSqlQuery query;
    query.prepare("SELECT id FROM tasks WHERE header = :header");
    query.bindValue(":header", header);

    if (!query.exec())
    {
        qDebug() << "Error executing query:" << query.lastError().text();
        return -1;
    }

    if (query.next())
    {
        auto result = query.value(0).toInt();
        return result;
    }

    return -1;
}
