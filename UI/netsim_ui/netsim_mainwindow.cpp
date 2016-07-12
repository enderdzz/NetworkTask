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
    //    current_frame = 0;
    //    frame_sender = new QTimer(this);
    //    connect(frame_sender, &QTimer::timeout, this, &Netsim_MainWindow::frame_send);

    //    frame_sender->setInterval(700);
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
        //calculate ui sizes here
        int width = ui->widgetWindowStatus->width();
        QString longest_str = QString::number(frame_count);
        QFontMetrics fm = ui->widgetWindowStatus->fontMetrics();
        int longest_length = fm.width(longest_str);
        const int block_height_padding = 10;
        const int block_width_padding = 5;
        int block_height = fm.height() +block_height_padding ;
        int block_width = longest_length + block_width_padding*2;
        block_count = width/block_width;

        ui->widgetWindowStatus->init_params(block_width, block_height, block_count, window_size);

        threadSender = new QThread;
        threadReceiver = new QThread;
        // have a fix
        workSender = new SimSender(frame_count,window_size,100);

        workReceiver = new SimReceiver(frame_count,window_size,100);
        ui->widget->graph_init(frame_count);
        workSender->moveToThread(threadSender);
        workReceiver->moveToThread(threadReceiver);

        connect(threadSender, &QThread::started, workSender, &SimSender::work);
        connect(threadReceiver, &QThread::started, workReceiver, &SimReceiver::work);

        connect(workSender, &SimSender::sendwindow_status,
                this, &Netsim_MainWindow::paint_update_gtt);
        connect(workSender, &SimSender::send_status,
                this, &Netsim_MainWindow::paint_update_gts);
        connect(workSender, &SimSender::finish_send,
                ui->widgetWindowStatus, &StatusWidget::finish_paint);
        connect(workSender, &SimSender::timeout_send,
                ui->widgetWindowStatus, &StatusWidget::trigger_blink);

        connect(workSender, &SimSender::send_status,
                ui->widget, &graphwidget::yvalue_insert);
        /*
        void send_status(int current_frame);
        void sendwindow_status(int current_left);*/
        //        ui->widgetWindowStatus, &StatusWidget::widget_update_paint_value);

//        connect(workSender, &SimSender::something_need_to_announce,
//                this, &Netsim_MainWindow::print_dbg_msg);
        //can just trigger repaint event here
        threadReceiver->start(QThread::LowestPriority);
        threadSender->start(QThread::LowestPriority);

//        on_btnOnOff_pressed();



    }else{
        threadReceiver->terminate();
        workReceiver->request_stop();
        threadReceiver->wait(100);
        qDebug("terminated");
        threadSender->terminate();
        workSender->request_stop();
        threadSender->wait(100);
        qDebug("waiting");


        disconnect(workSender, &SimSender::sendwindow_status,
                this, &Netsim_MainWindow::paint_update_gtt);
        disconnect(workSender, &SimSender::send_status,
                this, &Netsim_MainWindow::paint_update_gts);
        disconnect(workSender, &SimSender::finish_send,
                ui->widgetWindowStatus, &StatusWidget::finish_paint);
        disconnect(workSender, &SimSender::timeout_send,
                ui->widgetWindowStatus, &StatusWidget::trigger_blink);

        delete threadSender;
        delete threadReceiver;

  //      on_btnOnOff_pressed();
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

//void Netsim_MainWindow::frame_send()
//{
//    //this means a frame was sent
//    if (current_frame < frame_end){
//        current_frame++;
//        //QCoreApplication::postEvent(ui->widgetWindowStatus, new QPaintEvent(ui->widgetWindowStatus->rect()));
//        //QRect rect = ui->widgetWindowStatus->rect();
//        ui->widgetWindowStatus->repaint();
//    }
//}

void Netsim_MainWindow::paint_recalculate()
{
    //recalculate the block image


    //find right position of window block
    //Situation 1: [AB]CDEFGH
    //Situation 2: A[BC]DEFGH
    //Situation 3: DEF[GH]IJK
    //Situation 4 5 is similar with 1 and 2
    //Assume all start with 0
    int current_window = this->going_to_trigger;
    int draw_start;
    // this->window_size = window_size;

    if (! (current_window + window_size == frame_count)){
        //situation 1~4
        //judge situation 4
        if (current_window > frame_count - block_count/2 - window_size / 2)
        {
            //in situation 4
            draw_start = frame_count - (block_count - 1);
        } else if (current_window < block_count/2 - window_size / 2){
            draw_start = 0;
        } else {
            draw_start = current_window - (block_count/2 - window_size / 2);
        }
    } else{
        draw_start = frame_count - (block_count - 1);
    }


    ui->widgetWindowStatus->widget_update_paint_value(draw_start,
                                                      current_window,
                                                      this->going_to_send,
                                                      window_size);
    emit ui->widgetWindowStatus->repaint();

    //send block_count out for a try

}

void Netsim_MainWindow::paint_update_gts(int current_window)
{
    this->going_to_send = current_window;
    paint_recalculate();
}

void Netsim_MainWindow::paint_update_gtt(int current_window)
{
    this->going_to_trigger = current_window;
    paint_recalculate();
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
