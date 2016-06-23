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
    int on_radioArqBn_pressed();
    void widget_repaint();


private:
    Ui::Netsim_MainWindow *ui;
    QTimer* widget_refresh_timer;
};

#endif // NETSIM_MAINWINDOW_H
