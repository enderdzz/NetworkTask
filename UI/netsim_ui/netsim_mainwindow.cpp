#include "netsim_mainwindow.h"
#include "ui_netsim_mainwindow.h"
#include "dlgabout.h"
#include <QPainter>
#include <QTimer>
#include <QPaintEvent>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QThread>

Netsim_MainWindow::Netsim_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Netsim_MainWindow)
{
    ui->setupUi(this);
    //add a timer to refresh widget on time

    //add another timer, to automatically incrase
    //index 'current_frame'
    current_frame = 0;
    frame_sender = new QTimer(this);
    connect(frame_sender, &QTimer::timeout, this, &Netsim_MainWindow::frame_send);

    frame_sender->setInterval(700);
    //this is an example of how to use emit
    //see more about signal and slot at
    // https://doc.qt.io/qt-4.8/signalsandslots.html

    //ui->treeView->setModel(model);
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


 //   SimReceiver b;
    //convert status and refresh global var
    ui->widgetConfig->setEnabled(!ui->widgetConfig->isEnabled());
    isSimulationStarted = !ui->widgetConfig->isEnabled();

    if (isSimulationStarted){
        current_frame = 0;

        threadSender = new QThread;
        threadReceiver = new QThread;
        workSender = new SimSender;
        workReceiver = new SimReceiver;
        workSender->moveToThread(threadSender);
        workReceiver->moveToThread(threadReceiver);

        connect(threadSender, &QThread::started, workSender, &SimSender::work);
        connect(threadReceiver, &QThread::started, workReceiver, &SimReceiver::work);

        connect(workSender, &SimSender::something_need_to_announce,
                this, &Netsim_MainWindow::print_dbg_msg);
        connect(workReceiver, &SimReceiver::something_need_to_announce,
                this, &Netsim_MainWindow::print_dbg_msg);

        threadSender->start();
        threadReceiver->start();


    }else{
        threadSender->terminate();
        threadReceiver->terminate();
        threadSender->wait();
        threadReceiver->wait();



        delete threadSender;
        delete threadReceiver;
    }

}

int Netsim_MainWindow::on_radioArqSw_pressed()
{
    ui->groupWindowSize->setEnabled(false);
    ui->spinWindowSize->setValue(1);
    return 0;
}

int Netsim_MainWindow::on_radioArqBn_pressed(){
    ui->groupWindowSize->setEnabled(true);
    return 0;
}

void Netsim_MainWindow::widget_repaint(){
    ui->widgetWindowStatus->repaint();
}

void Netsim_MainWindow::frame_send()
{
    //this means a frame was sent
    if (current_frame < frame_end){
        current_frame++;
        //QCoreApplication::postEvent(ui->widgetWindowStatus, new QPaintEvent(ui->widgetWindowStatus->rect()));
        //QRect rect = ui->widgetWindowStatus->rect();
        ui->widgetWindowStatus->repaint();
    }
}

void Netsim_MainWindow::paint_recalculate()
{
    //this slot means we can recalculate the bitmap at here
    //this function will recalculate the bitmap

    //get device status
    int height = ui->widgetWindowStatus->height();
    int width = ui->widgetWindowStatus->width();

    //calculate longest font
    QString longest_str = QString::number(frame_end);
    QFontMetrics fm = ui->widgetWindowStatus->fontMetrics();
    int longest_text_length = fm.width(longest_str);

    //calculate block size
    const int block_height_padding = 10;
    const int block_width_padding = 5;
    int block_height = fm.height() +block_height_padding ;
    int block_width = longest_text_length + block_width_padding*2;

    //calculate block count
    int block_count = width/block_width;

    ui->widgetWindowStatus->widget_update_paint_value(block_width, block_height, current_frame,block_count);

    //send block_count out for a try

}

void Netsim_MainWindow::on_spinDataLength_editingFinished()
{
    if (ui->spinDataLength->value() < ui->spinWindowSize->value())
    {
        QMessageBox msgBox;
        msgBox.setText("Invaild DataLength!");
        msgBox.setInformativeText("Window size should be larget than length of data!");
        msgBox.setStandardButtons(QMessageBox::Ok |
                                  QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        msgBox.exec();
        ui->spinDataLength->setValue(ui->spinWindowSize->value()-1);
    }
}

void Netsim_MainWindow::on_spinWindowSize_editingFinished()
{
    if (ui->spinDataLength->value() < ui->spinWindowSize->value())
    {
        QMessageBox msgBox;
        msgBox.setText("Invaild DataLength!");
        msgBox.setInformativeText("Window size should be larget than length of data!");
        msgBox.setStandardButtons(QMessageBox::Ok |
                                  QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        msgBox.exec();
        ui->spinWindowSize->setValue(ui->spinDataLength->value()-1);
    }
}

void Netsim_MainWindow::on_actionQuit_triggered()
{
    emit on_btnQuit_pressed();
}

void Netsim_MainWindow::on_actionAbout_triggered()
{
  //  dlgAbout aboutdlg;
    QDialog *aboutdlg = new dlgAbout(this);

    aboutdlg->setModal(true);
    aboutdlg->show();
    aboutdlg->exec();
}

void Netsim_MainWindow::print_dbg_msg(const char* x)
{
    qDebug(x);
}
