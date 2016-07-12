#include "graphwidget.h"

graphwidget::graphwidget(QWidget *parent) : QWidget(parent)
{

}

void graphwidget::graph_init(int max_y)
{
    this->max_y = max_y;
    this->list_len = 0;
}

void graphwidget::yvalue_insert(int yvalue){
    struct timeval start;
    gettimeofday(&start, NULL);
    unsigned int t = start.tv_sec * 100 + start.tv_usec / 10000;
    data_list[list_len].calculated=false;
    data_list[list_len].time = t;
    data_list[list_len].data = yvalue;
    list_len++;
    this->repaint();
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

    //now paint points

    int x_size = this->width()-margin-margin;
    int y_size = this->height()-margin-margin;

    for ( int i = 0 ; i < list_len ; i++ ){
        if ( ! data_list[i].calculated ){
            data_list[i].ypos = this->height() - margin-
                            double(data_list[i].data*y_size) / (double)max_y ;
            data_list[i].xpos = margin + x_size * double(data_list[i].time - data_list[0].time) / (double)(data_list[list_len-1].time - data_list[0].time);
        }
        painter.drawEllipse(QPoint(data_list[i].xpos, data_list[i].ypos), 2, 2);
        painter.drawLine(QPoint(data_list[i].xpos, data_list[i].ypos),
                         i==0 ? QPoint(data_list[i].xpos, data_list[i].ypos)
                                :
                                QPoint(data_list[i-1].xpos, data_list[i-1].ypos));
    }

}
