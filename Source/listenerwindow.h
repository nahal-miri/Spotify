#ifndef LISTENERWINDOW_H
#define LISTENERWINDOW_H

#include <QDialog>

namespace Ui {
class ListenerWindow;
}

class ListenerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ListenerWindow(QWidget *parent = nullptr);
    ~ListenerWindow();

private:
    Ui::ListenerWindow *ui;
};

#endif // LISTENERWINDOW_H
