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
    widget_refresh_timer = new QTimer(this);
    connect(widget_refresh_timer, &QTimer::timeout, this, &Netsim_MainWindow::widget_repaint);
    widget_refresh_timer->setInterval(100);

    //add another timer, to automatically incrase
    //index 'current_frame'
    current_frame = 0;
    frame_sender = new QTimer(this);
    connect(frame_sender, &QTimer::timeout, this, &Netsim_MainWindow::frame_send);
    connect(frame_sender, &QTimer::timeout, this, &Netsim_MainWindow::paint_recalculate);
    frame_sender->setInterval(700);
    //this is an example of how to use emit
    //see more about signal and slot at
    // https://doc.qt.io/qt-4.8/signalsandslots.html
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
        current_frame = 0;
        frame_sender->start();
    }else{
        this->widget_refresh_timer->stop();
        frame_sender->stop();
    }

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

void Netsim_MainWindow::frame_send()
{
    //this means a frame was sent
    if (current_frame < frame_end){
        current_frame++;
    }
}

void Netsim_MainWindow::paint_recalculate()
{
    //this slot means we can recalculate the bitmap at here
    //this function will recalculate the bitmap

    //get device status
    int height = ui->widget->height();
    int width = ui->widget->width();

    //calculate longest font
    QString longest_str = QString::number(frame_end);
    QFontMetrics fm = ui->widget->fontMetrics();
    int longest_text_length = fm.width(longest_str);

    //calculate block size
    const int block_height_padding = 10;
    const int block_width_padding = 5;
    int block_height = fm.height() +block_height_padding ;
    int block_width = longest_text_length + block_width_padding*2;

    //calculate block count
    int block_count = width/block_width;

    ui->widget->widget_update_paint_value(block_width, block_height, current_frame,block_count);

    //send block_count out for a try

}
