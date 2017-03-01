#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    grabKeyboard();

    this->setFixedSize(QSize(662, 565));
    this->setWindowTitle("Snake");

    srand(time(NULL));

    field = new QTableWidget(ROWS,COLUMNS);
    field->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    field->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    field->verticalHeader()->hide();
    field->horizontalHeader()->hide();
    field->setSelectionMode(QAbstractItemView::NoSelection);
    field->setShowGrid(false);

    startBtn = new QPushButton("Start");
    stopBtn = new QPushButton("Retry");
    counter = new QLCDNumber();
    counter->setFixedSize(QSize(70,30));




    for( int i = 0; i < ROWS; i++ )
    {
        for( int j = 0 ; j < COLUMNS; j++ )
        {
            QTableWidgetItem* item = new QTableWidgetItem();
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            field->setItem(i,j, item);
        }
    }

    for(int i = 0; i < field->columnCount(); i++)
    {
        field->setColumnWidth(i, 35);
    }

    for(int i = 0; i < field->rowCount(); i++)
    {
        field->setRowHeight(i, 35);
    }

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(field);
    QVBoxLayout* vlayout = new QVBoxLayout;
    vlayout->addWidget(startBtn);
    vlayout->addWidget(stopBtn);

    QSpacerItem* spacerItem = new QSpacerItem(0,0,QSizePolicy::Minimum, QSizePolicy::Expanding);

    vlayout->addSpacerItem(spacerItem);
    vlayout->addWidget(counter);
    layout->addLayout(vlayout);
    this->setLayout(layout);


    for(int i = 0; i < snake.body().size(); i++)
    {
        field->item(snake.body()[i].rx(),snake.body()[i].ry())->setBackgroundColor(Qt::black);
    }
    connect(&snake, SIGNAL(drawSnake(QVector<QPoint>,QVector<QPoint>)),this, SLOT(drawSnakeSlot(QVector<QPoint>,QVector<QPoint>)));
    connect(startBtn, SIGNAL(clicked(bool)), this, SLOT(startGame()));
    connect(this, SIGNAL(gameOver()), this, SLOT(gameOverSlot()));
    connect(stopBtn, SIGNAL(clicked(bool)), this, SLOT(retryGame()));
    this->setFocusPolicy(Qt::StrongFocus);
    stopBtn->setEnabled(false);

}

Widget::~Widget()
{
    releaseKeyboard();
    delete ui;
}

void Widget::generateFood()
{
    srand(time(NULL));
    while(snake.body().contains(food))
    {
        food.setX(rand()%ROWS);
        food.setY(rand()%COLUMNS);
        qDebug() << food.rx() << food.ry();
    }
    field->item(food.rx(),food.ry())->setBackgroundColor(Qt::blue);
}

void Widget::drawSnakeSlot(QVector<QPoint> prev, QVector<QPoint> next)
{
    for(int i = 0; i < prev.size(); i++)
    {
        field->item(prev[i].rx(),prev[i].ry())->setBackgroundColor(Qt::white);
    }
    if(next[0] != food)
    {
        snake.noEat();
        next.pop_back();
    }
    else if(next[0] == food)
    {
        this->generateFood();
        counter->display(counter->value()+1);
    }

    if (prev.contains(next[0]))
    {
        emit gameOver();
    }

    for(int i = 0; i < next.size(); i++)
    {
        field->item(next[i].rx(),next[i].ry())->setBackgroundColor(Qt::black);
    }
}

void Widget::startGame()
{
    if(!snake.getTimer()->isActive())
    {
        snake.startTimer();
        this->generateFood();
        qDebug() << this->size();
        startBtn->setText("Stop");
    }
    else if(snake.getTimer()->isActive())
    {
        snake.stopTimer();
        startBtn->setText("Start");
    }

}

void Widget::retryGame()
{

    for(int i = 0; i < snake.body().size(); i++)
    {
        field->item(snake.body()[i].rx(),snake.body()[i].ry())->setBackgroundColor(Qt::white);
    }
    field->item(food.rx(),food.ry())->setBackgroundColor(Qt::yellow);

    snake.setDirection(Right);
    snake.setStartSize();

    counter->display(0);

    startBtn->setEnabled(true);
    stopBtn->setEnabled(false);


    snake.startTimer();
    this->generateFood();

}

void Widget::gameOverSlot()
{
     snake.stopTimer();
     startBtn->setEnabled(false);
     stopBtn->setEnabled(true);
}

void Widget::keyPressEvent(QKeyEvent *pe)
{
    switch (pe->key())
    {
    case Qt::Key_W:
    case Qt::Key_Up:
        qDebug() << "Press W";
        if(abs(snake.direction() - Up) != 2 && snake.direction() != Up)
        {
            snake.setDirection(Up);
        }
        break;
    case Qt::Key_A:
    case Qt::Key_Left:
        qDebug() << "Press A";
        if(abs(snake.direction() - Left) != 2 && snake.direction() != Left)
        {
            snake.setDirection(Left);
        }
        break;
    case Qt::Key_S:
    case Qt::Key_Down:
        qDebug() << "Press S";
        if(abs(snake.direction() - Down) != 2 && snake.direction() != Down)
        {
            snake.setDirection(Down);
        }
        break;
    case Qt::Key_D:
    case Qt::Key_Right:
        qDebug() << "Press D";
        if(abs(snake.direction() - Right) != 2 && snake.direction() != Right)
        {
            snake.setDirection(Right);
        }
        break;
    default:
        break;
    }

}


