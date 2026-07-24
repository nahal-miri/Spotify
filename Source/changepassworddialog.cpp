#include "changepassworddialog.h"
#include "ui_changepassworddialog.h"
#include <QMessageBox>
#include "../Repositories/accountrepository.h"

ChangePasswordDialog::ChangePasswordDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChangePasswordDialog)
{
    ui->setupUi(this);
}

ChangePasswordDialog::ChangePasswordDialog(std::shared_ptr<Account> account, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::ChangePasswordDialog),
    currentAccount(account) {
    ui->setupUi(this);
}

ChangePasswordDialog::~ChangePasswordDialog()
{
    delete ui;
}

void ChangePasswordDialog::on_saveButton_clicked()
{
    QString current = ui->currentPasswordLineEdit->text();
    QString newPass = ui->newPasswordLineEdit->text();
    QString confirm = ui->confirmPasswordLineEdit->text();

    if(current.toStdString() != currentAccount->getPassword()) {
        QMessageBox::warning(this, "Error","Current password is incorrect.");
        return;
    }

    if(newPass != confirm) {
        QMessageBox::warning(this, "Error", "Passwords do not match.");
        return;
    }

    currentAccount->changePassword(newPass.toStdString());

    accept();
}


void ChangePasswordDialog::on_cancelButton_clicked()
{
    reject();
}

