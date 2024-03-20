#include <QMessageBox>
#include "signupform.h"
#include "ui_signupform.h"
#include "sqlservice.h"
#include "stringhasher.h"

SignupForm::SignupForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SignupForm)
{
    ui->setupUi(this);
}

SignupForm::~SignupForm()
{
    delete ui;
}

void SignupForm::on_passwordLineEdit_textEdited(const QString &arg1)
{
    if(ui->passwordLineEdit->text() != "Password")
        ui->passwordLineEdit->setEchoMode(QLineEdit::Password);

    if(ui->nameLineEdit->text() == "")
        ui->nameLineEdit->setText("Name");

    if(ui->passwordAgainLineEdit->text() == ""){
        ui->passwordAgainLineEdit->setText("Password");
        ui->passwordAgainLineEdit->setEchoMode(QLineEdit::Normal);
    }
}


void SignupForm::on_passwordAgainLineEdit_textEdited(const QString &arg1)
{
    if(ui->passwordAgainLineEdit->text() != "Password")
        ui->passwordAgainLineEdit->setEchoMode(QLineEdit::Password);

    if(ui->nameLineEdit->text() == "")
        ui->nameLineEdit->setText("Name");

    if(ui->passwordLineEdit->text() == ""){
        ui->passwordLineEdit->setText("Password");
        ui->passwordLineEdit->setEchoMode(QLineEdit::Normal);
    }
}


void SignupForm::on_nameLineEdit_textEdited(const QString &arg1)
{
    if(ui->nameLineEdit->text().contains("Name"))
        ui->nameLineEdit->setText("");

    if(ui->passwordLineEdit->text() == ""){
        ui->passwordLineEdit->setText("Password");
        ui->passwordLineEdit->setEchoMode(QLineEdit::Normal);
    }

    if(ui->passwordAgainLineEdit->text() == ""){
        ui->passwordAgainLineEdit->setText("Password");
        ui->passwordAgainLineEdit->setEchoMode(QLineEdit::Normal);
    }
}


void SignupForm::on_logInPushButton_clicked()
{
    if(ui->nameLineEdit->text() == "Name"
        || ui->passwordLineEdit->text() == "Password"
        || ui->passwordAgainLineEdit->text() == "Password"
        || SqlService::CheckUserExists(ui->nameLineEdit->text()))
    {
        QMessageBox::critical(nullptr, "Помилка", "Incorrect data");
    }
    else if(ui->passwordLineEdit->text() == ui->passwordAgainLineEdit->text())
    {
        SqlService::AddUser(ui->nameLineEdit->text(), StringHasher::hashString(ui->passwordLineEdit->text()));
    }
    else
    {
        QMessageBox::critical(nullptr, "Помилка", "Incorrect data");
    }
}

