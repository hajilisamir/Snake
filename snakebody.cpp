#include "snakebody.h"
#include <QBrush>

SnakeBody::SnakeBody(QGraphicsItem *parent){
    // draw
    setRect(0,0,25,25);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::cyan);
    setBrush(brush);
}
