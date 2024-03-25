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

    if(selectedTask){
        for(auto& task : tasks) {
            if (task.GetHeader() == selectedTask->text()) {
                ui->descriptionPlainTextEdit->setPlainText(task.GetDescription());
            }
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




void MainWindow::on_removeTaskButton_clicked()
{
    if(selectedTask){
        SqlService::DeleteTask(user.GetId(), selectedTask->text());

        ui->tasksListWidget->clear();

        SqlService::GetUserTasks(std::ref(user));

        auto& tasks = user.GetTasks();

        for (auto& task : tasks) {
            ui->tasksListWidget->addItem(task.GetHeader());
        }

        selectedTask = nullptr;
    }
}




void MainWindow::on_addTaskButton_clicked()
{
    if(ui->taskHeaderPlainTextEdit->toPlainText() != "") {
        Task newTask(ui->taskHeaderPlainTextEdit->toPlainText());

        SqlService::AddTask(user, newTask);

        ui->taskHeaderPlainTextEdit->setPlainText("");

        ui->tasksListWidget->clear();

        SqlService::GetUserTasks(std::ref(user));

        auto& tasks = user.GetTasks();

        for (auto& task : tasks) {
            ui->tasksListWidget->addItem(task.GetHeader());
        }
    }
}
























