#ifndef NETSIM_MAINWINDOW_H
#define NETSIM_MAINWINDOW_H

#include <QMainWindow>
#include "including.h"
extern int showmsg();

namespace Ui {
class Netsim_MainWindow;
}

class Netsim_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit Netsim_MainWindow(QWidget *parent = 0);
    ~Netsim_MainWindow();

private slots:
    void on_btnQuit_pressed();
    void on_btnOnOff_pressed();
    int on_radioArqSw_pressed();
    int on_radioArqBn_pressed();
    void widget_repaint();
    //void frame_send(void);
    void paint_update_gts(int current_window);
    void paint_update_gtt(int current_window);
    void on_spinDataLength_editingFinished();
    void on_spinWindowSize_editingFinished();
    void on_actionQuit_triggered();
    void on_actionAbout_triggered();
    void print_dbg_msg(const char* x);

private:
    Ui::Netsim_MainWindow *ui;
    QTimer* widget_refresh_timer;
    QTimer* frame_sender;
    const int frame_count = 60;
    int block_count;
    int window_size = 8;
    int going_to_send = 0;
    int going_to_trigger = 0;
    //demo threader
    QThread *threadSender, *threadReceiver;
    SimSender* workSender;
    SimReceiver* workReceiver;
    bool isSimulationStarted = false;
    void paint_recalculate();
};

#endif // NETSIM_MAINWINDOW_H
