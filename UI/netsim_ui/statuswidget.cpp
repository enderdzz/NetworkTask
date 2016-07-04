#include "statuswidget.h"
#include "ui_statuswidget.h"
#include <QPainter>
#include <QMutexLocker>

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

void StatusWidget::widget_update_paint_value(int block_width, int block_height, int block_start_num, int block_count)
{
    QMutexLocker locker(&widget_value_busy);

    this->block_width = block_width;
    this->block_height = block_height;
    this->block_start_num = block_start_num;
    this->block_count = block_count;
}

void StatusWidget::paintEvent(QPaintEvent *event)
{
    QMutexLocker locker(&widget_value_busy);

    //need to get bitmap and paint it out
    /*
    static int x=0;
    QPainter painter(this);
    painter.setPen(Qt::gray); //设置画笔为灰色
    painter.drawLine(x++, 0, 100, 100); //(0, 0)为初始坐标，（100, 100）为最终坐标*/

    QPainter painter(this);
    QRect rectangle;
    QTextOption txtopt;

    int curX = 0;
    curX += block_width/2;
    rectangle.setY((this->height()-block_height)/2);
    for ( int i = 0 ; i < block_count ; i++){
        rectangle.setX(curX);
        curX += block_width;
        //reset width which changed by drawText
        rectangle.setWidth(block_width);
        rectangle.setHeight(block_height);
        painter.setPen(Qt::gray);
        painter.drawRect(rectangle);
        txtopt.setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
        painter.drawText(rectangle, QString::number(i+block_start_num),txtopt);
    }
    QBrush bsh;
    QPen pen;
    bsh.setColor(Qt::red);
    bsh.setStyle(Qt::Dense7Pattern);
    painter.setBrush(bsh);
    rectangle.setX(3*block_width);
    rectangle.setWidth(4*block_width);
    painter.drawRect(rectangle);

    //draw border
    //bsh
    bsh.setStyle(Qt::NoBrush);
    pen.setStyle(Qt::DotLine);
    pen.setWidthF(1.25);
    painter.setPen(pen);
    painter.setBrush(bsh);
    rectangle.setX(0);
    rectangle.setY(0);
    rectangle.setWidth(this->width());
    rectangle.setHeight(this->height());
    painter.drawRect(rectangle);

}