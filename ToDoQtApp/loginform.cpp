#include "loginform.h"
#include "ui_loginform.h"

LogInForm::LogInForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LogInForm)
{
    ui->setupUi(this);
}

LogInForm::~LogInForm()
{
    delete ui;
}
