#include "relationline.hpp"

//TODO: add types of relation
// 0 <- association (blue)
// 1 <- inheritance (red)
// 2 <- aggregation (green)
// 3 <- composition (black)


relationLine::relationLine(QWidget *parent ,QPoint p1, QPoint p2 , int type )
{

    //association
    QPalette Pal(palette());
    switch(type)
    {
     case 0: Pal.setColor(QPalette::Background, Qt::blue);
             break;
     case 1: Pal.setColor(QPalette::Background, Qt::red);
             break;
     case 2: Pal.setColor(QPalette::Background, Qt::green);
             break;
     case 3: Pal.setColor(QPalette::Background, Qt::black);
             break;
    }
    setAutoFillBackground(true);
    setPalette(Pal);


    //if return value 1 then is vertical line else is horizontal
    //this is vertical
    if(verticalOrHorizontal(p1,p2) == 1)
    {
        this->setFixedHeight(std::abs(p2.y() - p1.y()));
        this->setFixedWidth(2);
        this->move(p2.x(),p2.y());
    }
    //this is horizontal
    else
    {
        this->setFixedHeight(2);
        this->setFixedWidth(std::abs(p2.x() - p1.x()));
        this->move(p1.x(),p1.y());
    }

    this->setParent(parent);
    this->setCursor(Qt::OpenHandCursor);
    show();
}

int relationLine::verticalOrHorizontal(QPoint p1, QPoint p2){
    if(p1.x() == p2.x())
        return 1;
    else if(p1.y() == p2.y())
        return 2;
}
