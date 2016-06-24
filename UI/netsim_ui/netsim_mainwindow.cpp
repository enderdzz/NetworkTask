#include "netsim_mainwindow.h"
#include "ui_netsim_mainwindow.h"

Netsim_MainWindow::Netsim_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Netsim_MainWindow)
{
    ui->setupUi(this);
}

Netsim_MainWindow::~Netsim_MainWindow()
{
    delete ui;
}
