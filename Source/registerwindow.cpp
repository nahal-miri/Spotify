#include "registerwindow.h"
#include "ui_registerwindow.h"
#include <QMessageBox>
#include "../Repositories/artistrepository.h"
#include "../Repositories/listenerrepository.h"
#include "../Entities/artist.h"
#include "../Entities/listener.h"
#include "mainwindow.h"

RegisterWindow::RegisterWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);
}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}

void RegisterWindow::on_registerButton_clicked()
{
    QString fullName = ui->fullNameLineEdit->text();
    QString username = ui->userNameLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    QString bio = ui->bioLineEdit->text();

    if(fullName.isEmpty() || username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill all required fields.");
        return;
    }

    if(ListenerRepository::getInstance().searchByUserName(username.toStdString()) ||
        ArtistRepository::getInstance().searchByUserName(username.toStdString())) {
        QMessageBox::warning(this, "Error", "Username already exists.");
        return;
    }

    if(ui->roleComboBox->currentText() == "Listener") {
        auto listener = std::make_shared<Listener>(
            fullName.toStdString(),
            username.toStdString(),
            bio.toStdString(),
            password.toStdString()
            );

        int result = ListenerRepository::getInstance().save(listener);
        if(result == -1) {
            QMessageBox::warning(this, "Error", "Registration failed.");
            return;
        }
    }
    else {
        auto artist = std::make_shared<Artist>(
            fullName.toStdString(),
            username.toStdString(),
            bio.toStdString(),
            password.toStdString()
            );

        int result = ArtistRepository::getInstance().save(artist);
        if(result == -1) {
            QMessageBox::warning(this, "Error", "Registration failed.");
            return;
        }
    }

    QMessageBox::information(this, "Success", "Account created successfully.");
    MainWindow *window = new MainWindow();
    window->show();
    this->close();
}


void RegisterWindow::on_backButton_clicked()
{
    MainWindow *window = new MainWindow();
    window->show();
    this->close();
}