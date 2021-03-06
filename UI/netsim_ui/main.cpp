#include "netsim_mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include "including.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Netsim_MainWindow w;
    w.show();
    w.move((QApplication::desktop()->width() - w.width())/2, (QApplication::desktop()->height()-w.height())/2);

    return a.exec();
}

int showmsg(){
    QMessageBox msgBox;
    msgBox.setText("233");
    msgBox.setInformativeText("D231 save your changes?");
    msgBox.setStandardButtons(QMessageBox::Ok |
                              QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    return msgBox.exec()==QMessageBox::Ok;
}
