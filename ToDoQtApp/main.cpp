#include <QApplication>
#include "loginform.h"
#include "sqlservice.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SqlService::Connect();

    LogInForm w;
    w.show();
    return a.exec();
}
