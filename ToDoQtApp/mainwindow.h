#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include "user.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    MainWindow(User _user, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_tasksListWidget_itemPressed(QListWidgetItem *item);

    void on_saveDescriptionButton_clicked();

private:
    Ui::MainWindow *ui;

private:
    User user;
    QListWidgetItem *selectedTask;
};
#endif // MAINWINDOW_H
