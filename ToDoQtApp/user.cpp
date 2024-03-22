#include "user.h"
#include <QException>


User::User()
    : id(0), name("None"), password("None")
{ }

User::User(unsigned int _id, QString _name, QString _password, QList<Task> _tasks)
    : id(_id), name(_name), password(_password), tasks(_tasks)
{ }

unsigned int User::GetId() const {
    return id;
}

QString User::GetName() const {
    return name;
}

QString User::GetPassword() const {
    return password;
}

QList<Task>& User::GetTasks() {
    return tasks;
}

void User::SetId(unsigned int _id)
{
    id = _id;
}

void User::SetName(QString _name)
{
    name = _name;
}

void User::SetPassword(QString _password)
{
    password = _password;
}

void User::SetTasks(QList<Task> _tasks)
{
    tasks = _tasks;
}

void User::DeleteTask(QString _taskHeader) { // may be bug
    unsigned int index{};

    foreach(auto task, tasks)
        if(task.GetHeader() == _taskHeader)
            tasks.removeAt(index++);
        else
            index++;

}
