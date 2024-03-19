#ifndef USER_H
#define USER_H
#include "task.h"
#include <QList>


class User
{
    unsigned int id;
    QString name;
    QString password;
    QList<Task> tasks;

public:
    User(unsigned int _id, QString _name, QString _password, QList<Task> _tasks);

    unsigned int GetId() const;
    QString GetName() const;
    QString GetPassword() const;
    QList<Task> GetTasks() const;

    void AddTask(const Task& _task);
    void DeleteTask(QString _taskHeader);
};

#endif // USER_H
