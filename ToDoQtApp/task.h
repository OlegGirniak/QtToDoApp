#ifndef TASK_H
#define TASK_H
#include <QString>

class Task
{
    QString header;
    QString description;

public:
    Task(QString _header = "None", QString _description = "None");

    QString GetHeader() const;
    QString GetDescription() const;

    void ChangeDescription(QString _description);

    bool operator==(Task other);

};

#endif // TASK_H
