#include "editprofilewindow.h"
#include "Source/ui_editprofilewindow.h"
#include "../Repositories/listenerrepository.h"
#include <QMessageBox>
#include "changepasswordwindow.h"

EditProfileWindow::EditProfileWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditProfileWindow)
{
    ui->setupUi(this);
}

EditProfileWindow::EditProfileWindow(std::shared_ptr<Listener> listener, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::EditProfileWindow),
    currentListener(listener) {
    ui->setupUi(this);
    ui->fullNameLineEdit->setText(QString::fromStdString(currentListener->getFullName()));
    ui->userNameLineEdit->setText(QString::fromStdString(currentListener->getUserName()));
    ui->biotextEdit->setPlainText(QString::fromStdString(currentListener->getBio()));
}

EditProfileWindow::~EditProfileWindow()
{
    delete ui;
}

void EditProfileWindow::on_saveButton_clicked()
{
    QString fullName = ui->fullNameLineEdit->text().trimmed();
    QString userName = ui->userNameLineEdit->text().trimmed();
    QString bio = ui->biotextEdit->toPlainText().trimmed();

    if(fullName.isEmpty() || userName.isEmpty()) {
        QMessageBox::warning(this, "Error", "Full name and username cannot be empty.");
        return;
    }

    currentListener->setFullName(fullName.toStdString());
    currentListener->setUserName(userName.toStdString());
    currentListener->setBio(bio.toStdString());

    if(ListenerRepository::getInstance().save(currentListener) == -1) {
        QMessageBox::warning(this, "Error", "Profile update failed.");
        return;
    }

    QMessageBox::information(this, "Success", "Profile updated successfully.");
    accept();
}


void EditProfileWindow::on_cancelButton_clicked()
{
    reject();
}


void EditProfileWindow::on_changePasswordButton_clicked()
{
    ChangePasswordWindow dialog(currentListener, this);
    dialog.exec();
}

