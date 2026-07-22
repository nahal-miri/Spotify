#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include "Repositories/listenerrepository.h"
#include "Repositories/artistrepository.h"
#include "Exceptions/LoginException.h"
#include "artistwindow.h"
#include "listenerwindow.h"
#include "registerwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginButton_clicked()
{
    try {
        QString username = ui->usernameLineEdit->text();
        QString password = ui->passwordLineEdit->text();

        if(username.isEmpty() || password.isEmpty()) {
            QMessageBox::warning(this, "Error", "Please fill all fields.");
            return;
        }

        auto listener = ListenerRepository::getInstance().searchByUserName(username.toStdString());

        if(listener) {
            auto l = std::dynamic_pointer_cast<Listener>(*listener);

            if(l->getPassword() == password.toStdString()) {
                ListenerWindow *window = new ListenerWindow();
                window->show();
                this->close();
                return;
            }
        }

        auto artist = ArtistRepository::getInstance().searchByUserName(username.toStdString());

        if(artist) {
            auto a = std::dynamic_pointer_cast<Artist>(*artist);

            if(a->getPassword() == password.toStdString()) {
                ArtistWindow *window = new ArtistWindow(a);
                window->show();
                this->close();
                return;
            }
        }

        QMessageBox::warning(this, "Login Failed", "Username or password is incorrect.");

        throw LoginException("Username or password is incorrect.");
    }
    catch(const LoginException& e) {
        QMessageBox::warning(this, "Login Failed", e.what());
    }
}

void MainWindow::on_registerButton_clicked()
{
    RegisterWindow *window = new RegisterWindow();
    window->show();
    this->close();
}
