#include "snake.h"

Snake::Snake(QObject *parent) :
    QObject(parent)
{
    Direction = Right;

    Body.push_back(QPoint(5,7));
    Body.push_back(QPoint(5,6));
    Body.push_back(QPoint(5,5));
    Body.push_back(QPoint(5,4));


    timer = new QTimer();
    timer->setInterval(175);

    connect(timer, SIGNAL(timeout()), this, SLOT(move()));


}

Snake::~Snake()
{

}

void Snake::move()
{

    QVector<QPoint> temp;
    for(int i = 0; i < Body.size(); i++)
    {
        temp.push_back(QPoint(Body[i].rx(),Body[i].ry()));
    }

    for(int i = 0; i < temp.size(); i++)
    {
        //qDebug() << "temp " << temp[i].rx() << temp[i].ry();
    }

    if(Direction == Left)
    {
        Body[0].setY(--Body[0].ry());
    }
    else if(Direction == Right)
    {
        Body[0].setY(++Body[0].ry());
    }
    else if(Direction == Up)
    {
        Body[0].setX(--Body[0].rx());
    }
    else if(Direction == Down)
    {
        Body[0].setX(++Body[0].rx());
    }

    QPoint _head = Body[0];


    Body.clear();
    Body.push_back(_head);

    for(int i = 0; i < temp.size(); i++)
    {
        Body.push_back(temp[i]);
    }




    for(int i = 0; i < Body.size(); i++)
    {
        //qDebug() <<"body "<< Body[i].rx() << Body[i].ry();
    }
    //qDebug() << "---------------------------------------";

    for(int i = 0; i < Body.size(); i++)
    {
        QPoint tmp = Body[i];
     //   qDebug() << "tmp.rx() "<<tmp.rx();
        if(tmp.rx() >= ROW)
        {
            tmp.setX(tmp.rx() - ROW);
        }

        if(tmp.rx() < 0)
        {
            tmp.setX(tmp.rx() + ROW);
        }

        if(tmp.ry() >= COLUMN)
        {
            tmp.setY(tmp.ry() - COLUMN);
        }

        if(tmp.ry() < 0)
        {
           tmp.setY(tmp.ry() + COLUMN);
        }

        Body[i] = tmp;
       // qDebug() <<"---------------------"<< Body[i].rx() << Body[i].ry();
    }



    emit drawSnake(temp, Body);
}




QVector <QPoint> Snake::body() const
{
    return Body;
}

QPoint* Snake::head() const
{
    //return Head;
}

direct Snake::direction() const
{
    return Direction;
}

QTimer *Snake::getTimer() const
{
    return timer;
}

bool Snake::isDead() const
{
    return dead;
}

void Snake::setDead(bool d)
{
    dead = d;
}

void Snake::setDirection(direct dir)
{
    Direction = dir;
}

void Snake::setStartSize()
{
    Body.clear();
    Body.push_back(QPoint(5,7));
    Body.push_back(QPoint(5,6));
    Body.push_back(QPoint(5,5));
    Body.push_back(QPoint(5,4));
}

void Snake::startTimer()
{ 
    timer->start();
}

void Snake::stopTimer()
{
    timer->stop();
}

void Snake::noEat()
{
    Body.pop_back();
}

