#include "signupform.h"
#include "ui_signupform.h"

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
