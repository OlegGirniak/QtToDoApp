#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::MainWindow(User _user, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
    user(_user)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);


    auto tasks = user.GetTasks();

    for (auto& task : tasks) {
        ui->tasksListWidget->addItem(task.GetHeader());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    qApp->quit();
}

