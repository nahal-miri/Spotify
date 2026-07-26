#include "changepasswordwindow.h"
#include "Source/ui_changepasswordwindow.h"
#include <QMessageBox>
#include "../Repositories/listenerrepository.h"

ChangePasswordWindow::ChangePasswordWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChangePasswordWindow)
{
    ui->setupUi(this);
}

ChangePasswordWindow::ChangePasswordWindow(std::shared_ptr<Listener> listener, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::ChangePasswordWindow),
    currentListener(listener)
{
    ui->setupUi(this);

    ui->currentPasswordLineEdit->setEchoMode(QLineEdit::Password);
    ui->newPasswordLineEdit->setEchoMode(QLineEdit::Password);
    ui->confirmPasswordLineEdit->setEchoMode(QLineEdit::Password);
}

ChangePasswordWindow::~ChangePasswordWindow()
{
    delete ui;
}

void ChangePasswordWindow::on_saveButton_clicked()
{
    QString current = ui->currentPasswordLineEdit->text();
    QString newPass = ui->newPasswordLineEdit->text();
    QString repeat = ui->confirmPasswordLineEdit->text();

    if(current.toStdString() != currentListener->getPassword()) {
        QMessageBox::warning(this, "Error", "Current password is incorrect.");
        return;
    }

    if(newPass != repeat) {
        QMessageBox::warning(this, "Error", "Passwords do not match.");
        return;
    }

    if(newPass.isEmpty()) {
        QMessageBox::warning(this, "Error", "Password cannot be empty.");
        return;
    }

    currentListener->setPassword(newPass.toStdString());
    if(ListenerRepository::getInstance().save(currentListener) == -1) {
        QMessageBox::warning(this, "Error", "Password update failed.");
        return;
    }

    QMessageBox::information(this, "Success", "Password changed successfully.");
    accept();
}


void ChangePasswordWindow::on_cancelButton_clicked()
{
    reject();
}

