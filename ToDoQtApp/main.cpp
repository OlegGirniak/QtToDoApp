#include "mainwindow.h"
#include <QApplication>

#include "loginform.h"
#include "signupform.h"
#include "sqlservice.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    SqlService::Connect();
    w.show();
    return a.exec();
}
