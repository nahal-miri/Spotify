#ifndef ARTISTWINDOW_H
#define ARTISTWINDOW_H

#include <QDialog>

namespace Ui {
class ArtistWindow;
}

class ArtistWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ArtistWindow(QWidget *parent = nullptr);
    ~ArtistWindow();

private:
    Ui::ArtistWindow *ui;
};

#endif // ARTISTWINDOW_H
