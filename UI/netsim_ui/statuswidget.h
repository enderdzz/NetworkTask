#ifndef STATUSWIDGET_H
#define STATUSWIDGET_H

#include <QWidget>
#include <QMutex>

namespace Ui {
class StatusWidget;
}

class StatusWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StatusWidget(QWidget *parent = 0);
    ~StatusWidget();

public slots:
    void widget_update_paint_value(int draw_start,
                                   int current_window,
                                   int block_width,
                                   int block_height,
                                   int block_count,
                                   int window_size);

private:
    Ui::StatusWidget *ui;
    void paintEvent(QPaintEvent * event);
    QMutex widget_value_busy ;
    int block_width = 0;
    int block_height = 0;
    int block_count = 0;
    int current_window = 0;
    int draw_start = 0;
    int window_size = 0;
};

#endif // STATUSWIDGET_H
