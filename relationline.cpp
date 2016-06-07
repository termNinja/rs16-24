#include "relationline.hpp"

relationLine::relationLine(QWidget *parent ,QPoint p1, QPoint p2 )
{

    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::black);
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
