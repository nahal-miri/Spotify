#include "listenerwindow.h"
#include "ui_listenerwindow.h"

ListenerWindow::ListenerWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ListenerWindow)
{
    ui->setupUi(this);
}

ListenerWindow::~ListenerWindow()
{
    delete ui;
}
