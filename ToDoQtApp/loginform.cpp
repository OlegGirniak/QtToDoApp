#include "loginform.h"
#include "ui_loginform.h"
#include "sqlservice.h"



LogInForm::LogInForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LogInForm)
    , mainWindow(nullptr)
    , signUpform(nullptr)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
}

LogInForm::~LogInForm()
{
    if(ui)
        delete ui;
}

void LogInForm::on_logInPushButton_clicked()
{
    if(ui->nameLineEdit->text() != "" && ui->passwordLineEdit->text() != ""
        && (SqlService::CheckUserExists(ui->nameLineEdit->text())))
    {
        User currentUser = SqlService::GetUser(ui->nameLineEdit->text(), ui->passwordLineEdit->text());

        mainWindow = new MainWindow(currentUser, this);

        hide();
        mainWindow->activateWindow();
        mainWindow->show();
    }
}


void LogInForm::on_notHaveAccountButton_clicked()
{
    signUpform = new SignupForm();

    hide();
    signUpform->activateWindow();
    signUpform->show();

}

