#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>
#include "snake.h"
#include <cmath>
#include <time.h>
#include <stdlib.h>

const int COLUMNS = 15;
const int ROWS = 15;
namespace Ui {
class Widget;
}


class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
private:
    QTableWidget* field;
    QPushButton* startBtn;
    QPushButton* stopBtn;
    QLCDNumber* counter;

private:
    void generateFood();
private:
    Snake snake;
    QPoint food;
    int countFood;
public slots:
    void drawSnakeSlot(QVector<QPoint> prev, QVector<QPoint> next);
    void startGame();
    void retryGame();
    void gameOverSlot();
signals:
    void gameOver();

protected:
   virtual void keyPressEvent(QKeyEvent* pe);

};

#endif // WIDGET_H
