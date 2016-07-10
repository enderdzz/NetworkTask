#ifndef DLGABOUT_H
#define DLGABOUT_H

#include <QDialog>

namespace Ui {
class dlgAbout;
}

class dlgAbout : public QDialog
{
    Q_OBJECT

public:
    explicit dlgAbout(QWidget *parent = 0);
    ~dlgAbout();

private:
    Ui::dlgAbout *ui;
};

#endif // DLGABOUT_H
