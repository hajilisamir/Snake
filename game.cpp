#include "game.h"
#include "head.h"
#include "fruit.h"
#include "score.h"
#include <stdlib.h>
#include <QGraphicsTextItem>

Game::Game(QWidget *parent): QGraphicsView(parent){
    // set the scene

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene = new QGraphicsScene(0,0,624,624);
    setFixedSize(624,624);
    setScene(scene);

}

void Game::start(){
    // create snakeHead
    SnakeHead* snakeHead = new SnakeHead();
    scene->addItem(snakeHead);
    snakeHead->setFocus();
}

void Game::makeFruit()
{
    // create a fruit
    int random_number_x = (rand()%24)*26;
    int random_number_y = (rand()%24)*26;

    Fruit* f1 = new Fruit();
    f1->setPos(random_number_x,random_number_y);
    scene->addItem(f1);
}
