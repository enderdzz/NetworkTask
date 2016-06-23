#include "statuswidget.h"
#include "ui_statuswidget.h"
#include <QPainter>

StatusWidget::StatusWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatusWidget)
{
    ui->setupUi(this);
}

StatusWidget::~StatusWidget()
{
    delete ui;
}

void StatusWidget::paintEvent(QPaintEvent *event)
{
    static int x=0;
    QPainter painter(this);
    painter.setPen(Qt::gray); //设置画笔为灰色
    painter.drawLine(x++, 0, 100, 100); //(0, 0)为初始坐标，（100, 100）为最终坐标
}
