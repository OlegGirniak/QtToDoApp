#ifndef SIGNUPFORM_H
#define SIGNUPFORM_H

#include <QWidget>

namespace Ui {
class SignupForm;
}

class SignupForm : public QWidget
{
    Q_OBJECT

public:
    explicit SignupForm(QWidget *parent = nullptr);
    ~SignupForm();

private slots:
    void on_passwordLineEdit_textEdited(const QString &arg1);

    void on_passwordAgainLineEdit_textEdited(const QString &arg1);

    void on_nameLineEdit_textEdited(const QString &arg1);

    void on_logInPushButton_clicked();

private:
    Ui::SignupForm *ui;
};

#endif // SIGNUPFORM_H
