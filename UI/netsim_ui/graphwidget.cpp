#include "graphwidget.h"

graphwidget::graphwidget(QWidget *parent) : QWidget(parent)
{

}

void graphwidget::graph_init()
{
    yvalue_len = 0;
}

void graphwidget::yvalue_insert(int yvalue){
    yvalue_list[yvalue_len++] = yvalue;
    emit this->repaint();
}

void graphwidget::paintEvent(QPaintEvent *event)
{
    const double arrowhead_size = 20;
    const int margin = 10;
    const double arrowhead_hval = 0.55;
    const double arrowhead_wval = 0.2;

    //locate axis position
    QPoint origin;
    QPoint yaxis_endpoint;
    QPoint xaxis_endpoint;

    origin.setX(0 + margin);
    origin.setY(this->height() - margin);

    yaxis_endpoint.setX(0+margin);
    yaxis_endpoint.setY(0+margin);

    xaxis_endpoint.setX(this->width() - margin);
    xaxis_endpoint.setY(this->height() - margin);

    //locate poly location
    QPolygon xaxis_arrowhead;
    QPolygon yaxis_arrowhead;

    xaxis_arrowhead.resize(3);
    xaxis_arrowhead.setPoint(0,xaxis_endpoint);
    xaxis_arrowhead.setPoint(1,
                             xaxis_endpoint.x() - ceil(arrowhead_hval*arrowhead_size),
                             xaxis_endpoint.y() + ceil(arrowhead_wval*arrowhead_size));
    xaxis_arrowhead.setPoint(2,
                             xaxis_endpoint.x() - ceil(arrowhead_hval*arrowhead_size),
                             xaxis_endpoint.y() - floor(arrowhead_wval*arrowhead_size));
    yaxis_arrowhead.resize(3);
    yaxis_arrowhead.setPoint(0,yaxis_endpoint);
    yaxis_arrowhead.setPoint(1,
                             yaxis_endpoint.x() - floor(arrowhead_wval*arrowhead_size),
                             yaxis_endpoint.y() + ceil(arrowhead_hval*arrowhead_size));
    yaxis_arrowhead.setPoint(2,
                             yaxis_endpoint.x() + ceil(arrowhead_wval*arrowhead_size),
                             yaxis_endpoint.y() + ceil(arrowhead_hval*arrowhead_size));

    QPainter painter(this);
    painter.drawLine(origin, xaxis_endpoint);
    painter.drawLine(origin, yaxis_endpoint);
    painter.setBrush(QBrush(Qt::black, Qt::SolidPattern));
    painter.drawPolygon(xaxis_arrowhead);
    painter.drawPolygon(yaxis_arrowhead);

}
