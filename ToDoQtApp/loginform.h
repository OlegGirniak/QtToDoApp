#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include "mainwindow.h"
#include "signupform.h"

namespace Ui {
class LogInForm;
}

class LogInForm : public QWidget
{
    Q_OBJECT

public:
    explicit LogInForm(QWidget *parent = nullptr);

    ~LogInForm();

private slots:
    void on_logInPushButton_clicked();;

    void on_notHaveAccountButton_clicked();

private:
    Ui::LogInForm *ui;
    MainWindow* mainWindow;
    SignupForm* signUpform;
};

#endif // LOGINFORM_H
