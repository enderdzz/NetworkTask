#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include <QMutex>
#include <QPoint>
#include <QPolygon>
#include <QPainter>
#include <cmath>
#include <QBrush>
#include <sys/time.h>

class graphwidget : public QWidget
{
    Q_OBJECT
public:
    explicit graphwidget(QWidget *parent = 0);
    void graph_init(int max_y);

private:
    typedef struct STRUCT_node{
        bool calculated = false;
        int xpos;
        int ypos;
        int time;
        int data;
    } nodes;

    QMutex widget_value_busy;
    int list_len = 0;
    nodes data_list[200];
    int max_y = 0;

signals:

public slots:
    void yvalue_insert(int yvalue);
    void paintEvent(QPaintEvent *event);
};

#endif // GRAPHWIDGET_H
