#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sqlservice.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::MainWindow(User _user, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      user(_user),
      selectedTask(nullptr)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);


    auto& tasks = user.GetTasks();

    for (auto& task : tasks) {
        ui->tasksListWidget->addItem(task.GetHeader());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    qApp->quit();
}


void MainWindow::on_tasksListWidget_itemPressed(QListWidgetItem *item)
{
    selectedTask = item;

    auto& tasks = user.GetTasks();

    for(auto& task : tasks) {
        if (task.GetHeader() == item->text()) {
            ui->descriptionPlainTextEdit->clear();
            ui->descriptionPlainTextEdit->insertPlainText(task.GetDescription());
        }
    }
}


void MainWindow::on_saveDescriptionButton_clicked()
{
    auto& tasks = user.GetTasks();

    if(selectedTask){
        for(auto& task : tasks) {
            if (task.GetHeader() == selectedTask->text()) {
                task.ChangeDescription(ui->descriptionPlainTextEdit->toPlainText());
                SqlService::UpdateTask(task.GetHeader(), task.GetDescription());
            }
        }
    }
}



