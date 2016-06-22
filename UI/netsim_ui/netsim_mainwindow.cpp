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

void Netsim_MainWindow::on_btnQuit_pressed()
{
    qApp->exit();
}

void Netsim_MainWindow::on_btnOnOff_pressed(){
    QMessageBox msgBox;
    msgBox.setText("Name");
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard |
                              QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    msgBox.exec();
}

int Netsim_MainWindow::on_radioArqBn_pressed(){
    if (showmsg())
        ui->radioArqBn->setChecked(true);
    else
        ui->radioArqSw->setChecked(true);

}
