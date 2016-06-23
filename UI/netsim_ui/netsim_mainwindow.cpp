#include "netsim_mainwindow.h"
#include "ui_netsim_mainwindow.h"

#include <QPainter>
#include <QTimer>

Netsim_MainWindow::Netsim_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Netsim_MainWindow)
{
    ui->setupUi(this);
    //add a timer to refresh widget on time
    this->widget_refresh_timer = new QTimer(this);
    connect(this->widget_refresh_timer, SIGNAL(timeout()), this, SLOT(widget_repaint()));
    this->widget_refresh_timer->setInterval(100);
   // this->widget_refresh_timer->start();
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
    isSimulationStarted = !ui->widgetConfig->isEnabled();

    if (isSimulationStarted){
        this->widget_refresh_timer->start();
    }else{
        this->widget_refresh_timer->stop();
    }

    //this is an example of how to use emit
    //see more about signal and slot at
    // https://doc.qt.io/qt-4.8/signalsandslots.html
}


int Netsim_MainWindow::on_radioArqBn_pressed(){
    if (showmsg())
        ui->radioArqBn->setChecked(true);
    else
        ui->radioArqSw->setChecked(true);

    return 0;
}

void Netsim_MainWindow::widget_repaint(){
    ui->widget->repaint();
}
