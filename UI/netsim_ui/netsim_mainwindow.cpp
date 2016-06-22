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
    //convert status and refresh global var
    ui->widgetConfig->setEnabled(!ui->widgetConfig->isEnabled());
    isSimulationStarted = ui->widgetConfig->isEnabled();

    //this is an example of how to use emit
    //see more about signal and slot at
    // https://doc.qt.io/qt-4.8/signalsandslots.html
    emit on_btnQuit_pressed();
}

int Netsim_MainWindow::on_radioArqBn_pressed(){
    if (showmsg())
        ui->radioArqBn->setChecked(true);
    else
        ui->radioArqSw->setChecked(true);


    return 0;
}
