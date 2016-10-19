#ifndef SNAKEHEAD_H
#define SNAKEHEAD_H

#include "snakebody.h"
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QList>
#include <QPointF>
#include <QTimer>

class SnakeHead: public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    // constructors
    SnakeHead(QGraphicsItem* parent=NULL);

    // events
    void keyPressEvent(QKeyEvent* event);

    // public method
    void elongate();
    void moveBodies();
    void stop();
    void checkBorder();
    QTimer *timer = new QTimer();
public slots:
    void up();
    void down();
    void left();
    void right();


private:
    QList<SnakeBody*> snakeBodies;
    QPointF prevPos;
};

#endif // SNAKEHEAD_H
