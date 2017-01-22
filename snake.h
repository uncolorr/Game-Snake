#ifndef SNAKE_H
#define SNAKE_H

#include <QtWidgets>
#include <QStack>

const int COLUMN = 15;
const int ROW = 15;
enum direct {Up = 1, Left, Down, Right};

class Snake : public QObject
{
    Q_OBJECT
public:
    explicit Snake(QObject *parent = 0);
    ~Snake();

signals:
    void drawSnake(QVector<QPoint> prev, QVector<QPoint> next);
public slots:
    void move();
private:

    QVector<QPoint> Body;
    direct Direction;
    QTimer* timer;
    bool dead;


public:
    QVector<QPoint> body() const;
    QPoint* head() const;
    direct direction() const;
    QTimer* getTimer() const;
    bool isDead() const;
    void setDead(bool d);


    void setDirection(direct dir);
    void setStartSize();
    void startTimer();
    void stopTimer();
    void noEat();
protected:


};

#endif // SNAKE_H
