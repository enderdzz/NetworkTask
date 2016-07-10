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

void StatusWidget::init_params(int block_width,
                               int block_height,
                               int block_count,
                               int window_size){
    QMutexLocker locker(&widget_value_busy);
    this->block_width = block_width;
    this->block_height = block_height;
    this->block_count = block_count;
    this->window_size = window_size;
}

void StatusWidget::widget_update_paint_value(int draw_start,
                                             int current_window,
                                             int current_trig,
                                             int window_size)
{
    QMutexLocker locker(&widget_value_busy);

    this->draw_start = draw_start;
    this->current_window = current_window;
    this->window_size = window_size;
    this->current_trig=current_trig;
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
    for ( int i = draw_start ; i < draw_start+block_count-1 ; i++){
        rectangle.setX(curX);
        curX += block_width;
        //reset width which changed by drawText
        rectangle.setWidth(block_width);
        rectangle.setHeight(block_height);
        painter.setPen(Qt::gray);
        painter.drawRect(rectangle);
        txtopt.setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
        painter.drawText(rectangle, QString::number(i),txtopt);
    }
    QBrush bsh;
    QPen pen;
    bsh.setColor(Qt::green);
    bsh.setStyle(Qt::Dense7Pattern);
    painter.setBrush(bsh);
    rectangle.setX((current_window - draw_start + 0.5)*block_width);
    rectangle.setWidth((current_trig - current_window)*block_width);
    painter.drawRect(rectangle);
    bsh.setColor(Qt::red);
    painter.setBrush(bsh);
    rectangle.setX((current_trig - draw_start + 0.5)*block_width);
    rectangle.setWidth((window_size-(current_trig-current_window))*block_width);
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
