#include "user.h"
#include <QException>


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

QList<Task> User::GetTasks() const {
    return tasks;
}

void User::AddTask(const Task& _task) {
    //if (!tasks.contains(_task))
       // tasks.append(_task);
   // else
//throw QException();
}

void User::DeleteTask(QString _taskHeader) { // may be bug
    unsigned int index{};

    foreach(auto task, tasks)
        if(task.GetHeader() == _taskHeader)
            tasks.removeAt(index++);
        else
            index++;

}
