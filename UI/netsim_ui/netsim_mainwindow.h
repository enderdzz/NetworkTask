#ifndef NETSIM_MAINWINDOW_H
#define NETSIM_MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::Netsim_MainWindow *ui;
};

#endif // NETSIM_MAINWINDOW_H
