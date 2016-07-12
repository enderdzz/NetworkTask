#include "statuswidget.h"
#include "ui_statuswidget.h"
#include <QPainter>
#include <unistd.h>
#include <QMutexLocker>
#include <QTimer>

StatusWidget::StatusWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatusWidget)
{
    ui->setupUi(this);
    blinker = new QTimer;
    blinkcontroller = new QTimer;
    blinker->setInterval(100);
    blinker->stop();
    blinkcontroller->stop();
    connect(blinker, &QTimer::timeout,
            this, &StatusWidget::blinker_timeout);
    connect(blinkcontroller, &QTimer::timeout,
            this, &StatusWidget::blinkercontroller_timeout);

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

void StatusWidget::finish_paint()
{
    this->current_window = 0xffff;
    this->repaint();
}

void StatusWidget::trigger_blink()
{
    blinkcontroller->setSingleShot(true);
    blinkcontroller->setInterval(500);
    blinkcontroller->start();
    blinker->start();
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
    QBrush bsh;
    QPen pen;

    //Four areas are concerned:
    // [Succeed] [Succeed in this session] [Not okay yet] [Not sent yet]
    int curX = block_width/2;   //have left margin
    int curY = (this->height()-block_height)/2;
    rectangle.setX(curX); rectangle.setY(curY);

    for ( int i = draw_start ; i < draw_start+block_count-1; i++){

        //set pen style
        if (i>=0 && i<current_window){
            //succeed area
            bsh.setStyle(Qt::NoBrush);
            pen.setStyle(Qt::SolidLine);
            pen.setColor(Qt::gray);
        }else if (i >= current_window && i < current_trig ){
            //succeed_in_this_session
            bsh.setStyle(Qt::SolidPattern);
            bsh.setColor(QColor(0,255,0,160));
            pen.setStyle(Qt::SolidLine);
            pen.setColor(Qt::black);
        }else if (i >= current_trig && i < window_size + current_window ){
            //not_okay_yet
            bsh.setStyle(Qt::SolidPattern);
            bsh.setColor(QColor(255,0,0,160));
            pen.setStyle(Qt::SolidLine);
            pen.setColor(Qt::black);
        }else{
            //not_sent_yet
            bsh.setStyle(Qt::NoBrush);
            pen.setStyle(Qt::SolidLine);
            pen.setColor(Qt::black);
        }
        painter.setPen(pen);
        painter.setBrush(bsh);

        //draw rectangle and number
        rectangle.setX(curX);
        curX += block_width;
        //reset width which changed by drawText
        rectangle.setWidth(block_width);
        rectangle.setHeight(block_height);
        painter.drawRect(rectangle);
        txtopt.setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
        painter.drawText(rectangle, QString::number(i),txtopt);

    }

    //draw border
    //bsh
    if (show_blink_block){
        rectangle.setX(0);
        rectangle.setY(0);
        rectangle.setWidth(this->width());
        rectangle.setHeight(this->height());
        painter.setCompositionMode(QPainter::CompositionMode_Darken);
        bsh.setStyle(Qt::SolidPattern);
        bsh.setColor(QColor(0,0,0,60));
        painter.setPen(pen);
        painter.setBrush(bsh);
        painter.drawRect(rectangle);
        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    }
    bsh.setStyle(Qt::NoBrush);
    pen.setStyle(Qt::DotLine);
    pen.setColor(Qt::gray);
    pen.setWidthF(1.25);
    painter.setPen(pen);
    painter.setBrush(bsh);
    rectangle.setX(0);
    rectangle.setY(0);
    rectangle.setWidth(this->width());
    rectangle.setHeight(this->height());
    painter.drawRect(rectangle);
}

void StatusWidget::blinker_timeout()
{
    show_blink_block = !show_blink_block;
    this->repaint();
}

void StatusWidget::blinkercontroller_timeout(){
    blinker->stop();
    show_blink_block = false;
    this->repaint();
}
