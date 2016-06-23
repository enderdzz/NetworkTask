#ifndef STATUSWIDGET_H
#define STATUSWIDGET_H

#include <QWidget>

namespace Ui {
class StatusWidget;
}

class StatusWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StatusWidget(QWidget *parent = 0);
    ~StatusWidget();

private:
    Ui::StatusWidget *ui;

    void paintEvent(QPaintEvent * event);
};

#endif // STATUSWIDGET_H
