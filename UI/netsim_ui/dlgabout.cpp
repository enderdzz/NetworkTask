#include "dlgabout.h"
#include "ui_dlgabout.h"

dlgAbout::dlgAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgAbout)
{
    ui->setupUi(this);
}

dlgAbout::~dlgAbout()
{
    delete ui;
}
