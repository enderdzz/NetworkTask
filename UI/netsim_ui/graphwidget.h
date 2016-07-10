#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include <QMutex>
#include <QPoint>
#include <QPolygon>
#include <QPainter>
#include <cmath>
#include <QBrush>

class graphwidget : public QWidget
{
    Q_OBJECT
public:
    explicit graphwidget(QWidget *parent = 0);
    void graph_init();

private:
    QMutex widget_value_busy;
    int yvalue_list[200];
    int yvalue_len = 0;

signals:

public slots:
    void yvalue_insert(int yvalue);
    void paintEvent(QPaintEvent *event);
};

#endif // GRAPHWIDGET_H
