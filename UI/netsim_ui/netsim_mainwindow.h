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
    void frame_send(void);
    void paint_recalculate(void);


    void on_spinDataLength_editingFinished();

    void on_spinWindowSize_editingFinished();

    void on_actionQuit_triggered();

    void on_actionAbout_triggered();

private:
    Ui::Netsim_MainWindow *ui;
    QTimer* widget_refresh_timer;
    QTimer* frame_sender;
    const int frame_begin = 0;
    const int frame_end = 15;
    const int window_size = 4;
    int current_frame = 0;
    //demo threader
    QThread* athread;
};

#endif // NETSIM_MAINWINDOW_H
