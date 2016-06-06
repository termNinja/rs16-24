#include "relationline.hpp"

relationLine::relationLine(QWidget *parent ,QPoint p1, QPoint p2 )
{

    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::black);
    setAutoFillBackground(true);
    setPalette(Pal);

    //if return value 1 then is vertical line else is horizontal
    if(verticalOrHorizontal(p1,p2) == 1)
    {
        this->setFixedHeight(500);
        this->setFixedWidth(2);
    }
    else
    {
        this->setFixedHeight(2);
        this->setFixedWidth(500);
    }

    this->setParent(parent);
    this->setCursor(Qt::OpenHandCursor);
    this->move(40,40);
    show();
}

int relationLine::verticalOrHorizontal(QPoint p1, QPoint p2){
    if(p1.x() == p2.x())
        return 1;
    else if(p1.y() == p2.y())
        return 2;
}
