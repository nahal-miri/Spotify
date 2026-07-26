#include "listenerprofilewindow.h"
#include "Source/ui_listenerprofilewindow.h"
#include "editprofilewindow.h"
#include <QMessageBox>
#include "../Repositories/listenerrepository.h"

ListenerProfileWindow::ListenerProfileWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ListenerProfileWindow)
{
    ui->setupUi(this);
}

ListenerProfileWindow::ListenerProfileWindow(std::shared_ptr<Listener> listener, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::ListenerProfileWindow),
    currentListener(listener) {
    ui->setupUi(this);
    ui->fullNameLabel->setText(QString::fromStdString(currentListener->getFullName()));
    ui->userNameLabel->setText(QString::fromStdString(currentListener->getUserName()));
    ui->bioLabel->setText(QString::fromStdString(currentListener->getBio()));
}

ListenerProfileWindow::~ListenerProfileWindow()
{
    delete ui;
}

void ListenerProfileWindow::on_editProfileButton_clicked()
{
    EditProfileWindow dialog(currentListener, this);

    if(dialog.exec() == QDialog::Accepted) {
        ui->fullNameLabel->setText(QString::fromStdString(currentListener->getFullName()));
        ui->userNameLabel->setText(QString::fromStdString(currentListener->getUserName()));
        ui->bioLabel->setText(QString::fromStdString(currentListener->getBio()));
    }
}
void ListenerProfileWindow::on_deleteAccountButton_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Delete Account", "Are you sure?", QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::No)
        return;

    ListenerRepository::getInstance().remove(currentListener->getId());
    accept();
}
