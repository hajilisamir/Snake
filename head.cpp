#include "head.h"
#include <QBrush>
#include "fruit.h"
#include "snakebody.h"
#include "game.h"
#include "score.h"

extern Game* game;

SnakeHead::SnakeHead(QGraphicsItem *parent){
    // draw
    setRect(0,0,25,25);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::blue);
    setBrush(brush);

    // make focusable
    setFlag(QGraphicsItem::ItemIsFocusable,true);

    // TODO remove, test
    SnakeBody* b1 = new SnakeBody();
    b1->setPos(0,25);
    game->scene->addItem(b1);
    snakeBodies.prepend(b1);
}

void SnakeHead::keyPressEvent(QKeyEvent *event){
    // move up
    if (event->key() == Qt::Key_Up){
        stop();
        connect(timer,SIGNAL(timeout()),this,SLOT(up()));
    }
    if (event->key() == Qt::Key_Down){
        stop();
        connect(timer,SIGNAL(timeout()),this,SLOT(down()));
    }
    if (event->key() == Qt::Key_Right){
        stop();
        connect(timer,SIGNAL(timeout()),this,SLOT(right()));
    }
    if (event->key() == Qt::Key_Left){
        stop();
        connect(timer,SIGNAL(timeout()),this,SLOT(left()));
    }
    if (event->key() == Qt::Key_F5)
    {
        stop();
    }
    timer->start(120);
}

void SnakeHead::elongate(){
    // add new SnakeBody to list
    SnakeBody* body = new SnakeBody();
    snakeBodies.prepend(body);

    // properly position the body
    body->setPos(-200,-200); // TODO
    game->scene->addItem(body);
}

void SnakeHead::moveBodies(){
    // traverses through list of bodies and moves them properly
    // move all bodies from back to front
    for (size_t i = 0, n = snakeBodies.size()-1; i < n; ++i){
        snakeBodies[i]->setPos(snakeBodies[i+1]->pos());
    }
    // move front body to previous position of head
    snakeBodies.last()->setPos(prevPos);
}

void SnakeHead::stop()
{
    disconnect(timer,SIGNAL(timeout()),this,SLOT(left()));
    disconnect(timer,SIGNAL(timeout()),this,SLOT(right()));
    disconnect(timer,SIGNAL(timeout()),this,SLOT(down()));
    disconnect(timer,SIGNAL(timeout()),this,SLOT(up()));
}

void SnakeHead::checkBorder()
{
    if(x()>600 || x()<0 || y()<0 || y()>600)
    {
        stop();
        scene()->removeItem(this);
    }
    // elongate if collides with Fruit
    QList<QGraphicsItem*> cItems = collidingItems();
    for (size_t i = 0, n = cItems.size(); i < n; ++i){
        if (typeid(*cItems[i]) == typeid(Fruit)){
            // fruit found in collision list
            elongate();
            delete cItems[i];
            game->makeFruit();
            //increase();
        }
    }

    //Game Over eating Tail
    QList<QGraphicsItem*> cItems1 = collidingItems();
    for (size_t i = 0, n = cItems1.size(); i < n; ++i){
        if (typeid(*cItems1[i]) == typeid(SnakeBody)){
            scene()->removeItem(this);
            stop();
        }
    }
}

void SnakeHead::up()
{
    prevPos = pos();
    int xPos = x();
    int yPos = y() - boundingRect().width();
    setPos(xPos,yPos);
    moveBodies();
    checkBorder();
}
void SnakeHead::down()
{
    prevPos = pos();
    int xPos = x();
    int yPos = y() + boundingRect().width();
    setPos(xPos,yPos);
    moveBodies();
    checkBorder();
}
void SnakeHead::left()
{
    prevPos = pos();
    int xPos = x() - boundingRect().width();
    int yPos = y();
    setPos(xPos,yPos);
    moveBodies();
    checkBorder();
}
void SnakeHead::right()
{
    prevPos = pos();
    int xPos = x() + boundingRect().width();
    int yPos = y();
    setPos(xPos,yPos);
    moveBodies();
    checkBorder();
}
