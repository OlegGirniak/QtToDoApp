#include "task.h"


Task::Task(QString _header, QString _description)
    : header(_header), description(_description)
{ }

QString Task::GetHeader() const {
    return header;
}

QString Task::GetDescription() const {
    return description;
}

void Task::ChangeDescription(QString _description) {
    description = _description;
}

bool Task::operator==(Task other)
{
    return this->header == other.header;
}
