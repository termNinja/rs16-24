#include "relationwidget.hpp"


relationWidget::relationWidget(QWidget *parent ,ClassWidget *class1, ClassWidget *class2, int type){

    std::vector<QPoint> pointsOfClass1 = getFourPoints(class1->pos() , class1->width() , class1->height());
    std::vector<QPoint> pointsOfClass2 = getFourPoints(class2->pos() , class2->width() , class2->height());
    std::vector<QPoint> minDistTwoPoints = minDist(pointsOfClass1 , pointsOfClass2);

    m_firstClass = class1;
    m_secondClass = class2;
    makeRelation(parent , minDistTwoPoints , type , class1 , class2);
}

ClassWidget* relationWidget::getFirstClass(){
    return m_firstClass;
}

int relationWidget::getType()
{
    return m_type;
}

ClassWidget* relationWidget::getSecondClass(){
    return m_secondClass;
}

void relationWidget::makeRelation(QWidget *parent , std::vector<QPoint> minDistTwoPoints, int type
                  ,ClassWidget *class1, ClassWidget *class2){

    QPoint startPoint = minDistTwoPoints.at(0);
    QPoint endPoint   = minDistTwoPoints.at(1);
    QPoint tmpPointClass1;
    QPoint tmpPointClass2;

    std::cout<<startPoint.x() << " " <<startPoint.y()<<std::endl;
    std::cout<<endPoint.x() << " " <<endPoint.y()<<std::endl;

    relationLine *bonusLineClass1 ;
    switch(m_firstClassPointPosition)
    {
        case 0: tmpPointClass1 = QPoint( startPoint.x() - 10 , startPoint.y());
                bonusLineClass1 = new relationLine(parent,tmpPointClass1,startPoint, type);
                break;

        case 1: tmpPointClass1 = QPoint( startPoint.x() , startPoint.y()+10);
                bonusLineClass1 = new relationLine(parent , tmpPointClass1,startPoint , type);
                break;

        case 2: tmpPointClass1 = QPoint( startPoint.x() + 10 , startPoint.y());
                bonusLineClass1 = new relationLine(parent ,startPoint , tmpPointClass1 , type);
                break;

        case 3: tmpPointClass1 =  QPoint( startPoint.x() , startPoint.y()-10);
                bonusLineClass1 = new relationLine(parent ,startPoint , tmpPointClass1 , type);
                break;
    }


    relationLine *bonusLineClass2 ;
    switch( m_secondClassPointPosition )
    {
        case 0: tmpPointClass2 = QPoint( endPoint.x() - 10 ,  endPoint.y());
                bonusLineClass2 = new relationLine(parent,tmpPointClass2,endPoint, type);
                break;

        case 1: tmpPointClass2 = QPoint(  endPoint.x() ,  endPoint.y()+10);
                bonusLineClass2 = new relationLine(parent ,
                                                   tmpPointClass2, endPoint , type);
                break;

        case 2: tmpPointClass2 = QPoint(  endPoint.x() + 10 ,  endPoint.y());
                bonusLineClass2 = new relationLine(parent , endPoint , tmpPointClass2, type);
                break;

        case 3: tmpPointClass2 =  QPoint(  endPoint.x() ,  endPoint.y()-10);
                bonusLineClass2 = new relationLine(parent , endPoint , tmpPointClass2, type );
                break;
    }

    if ( class1->pos().x() < class2->pos().x() &&
         class1->pos().y() > class2->pos().y())
    {
     relationLine *firstLine = new relationLine(parent ,tmpPointClass1 ,
                                                QPoint( tmpPointClass2.x() , startPoint.y()), type);

     relationLine *secondLine = new relationLine(parent ,QPoint( tmpPointClass2.x() , startPoint.y()) ,
                                                 tmpPointClass2 , type);
    }

    if ( class1->pos().x() < class2->pos().x() &&
         class1->pos().y() < class2->pos().y())
    {

     relationLine *firstLine = new relationLine(parent ,tmpPointClass1 ,
                                                QPoint( tmpPointClass2.x() , startPoint.y()), type);

     relationLine *secondLine = new relationLine(parent , tmpPointClass2 ,
                                                 QPoint( tmpPointClass2.x() , startPoint.y()) , type);
    }

    if ( class1->pos().x() > class2->pos().x() &&
         class1->pos().y() < class2->pos().y())
    {

     relationLine *firstLine = new relationLine(parent ,
                                                QPoint( tmpPointClass2.x() , startPoint.y()) ,tmpPointClass1
                                                , type);

     relationLine *secondLine = new relationLine(parent , tmpPointClass2 ,
                                                 QPoint( tmpPointClass2.x() , startPoint.y()) , type );
    }

    if ( class1->pos().x() > class2->pos().x() &&
         class1->pos().y() > class2->pos().y())
    {

     relationLine *firstLine = new relationLine(parent ,
                                                QPoint( tmpPointClass2.x() , startPoint.y()) ,tmpPointClass1
                                                , type);

     relationLine *secondLine = new relationLine(parent ,
                                                 QPoint( tmpPointClass2.x() , startPoint.y())  , tmpPointClass2
                                                 , type);
    }

}

int relationWidget::numberOfLines(QPoint p1, QPoint p2 ){
    return 2;
}

std::vector<QPoint> relationWidget::getFourPoints(QPoint pos , int width , int height){
    std::vector<QPoint> vector;
    int x = pos.x();
    int y = pos.y();
    //left edge point
    vector.push_back(QPoint( x ,  (height/2) + y ));
    //bottom edge point
    vector.push_back(QPoint( x + (width/2) , y + height ));
    //right edge point
    vector.push_back(QPoint( x + width , (height/2) + y ));
    //top edge point
    vector.push_back(QPoint( x + (width/2) , y ));

    return vector;
}

std::vector<QPoint> relationWidget::minDist(std::vector<QPoint> &class1 , std::vector<QPoint> &class2){

    int positionClass1=0;
    int positionClass2=0;
    std::vector<QPoint> returnValue;

    int i=0;
    int j=0;
    //inicijalni min

    QPoint first = class1.at(0);
    QPoint second = class2.at(0);
    double minDist = sqrt(pow(first.x() - second.x() , 2) + pow(first.y() - second.y(),2));

    std::cout<<"Dist"  << minDist <<std::endl;
    for ( int i=0; i < 4 ; i++ ) {
        for ( int j=0 ; j< 4 ; j++) {
            std::cout<<"i:" << i << std::endl;
            std::cout<<"j:" << j<< std::endl ;
              QPoint first = class1.at(i);
              QPoint second = class2.at(j);
              double tmpMinDist = sqrt(pow(first.x() - second.x() , 2) + pow(first.y() - second.y(),2));
              std::cout<<"nreDist"  << tmpMinDist <<std::endl;
              if(tmpMinDist < minDist)
              {
                positionClass1 = i;
                positionClass2 = j;
                minDist = tmpMinDist;
              }
        }

        std::cout<<"posi:" << positionClass1 << std::endl;
        std::cout<<"posj:" << positionClass2<< std::endl ;
    }
    m_firstClassPointPosition = positionClass1;
    m_secondClassPointPosition = positionClass2;

    returnValue.push_back(class1.at(positionClass1));
    returnValue.push_back(class2.at(positionClass2));

    return returnValue;
}

//TODO: odradi lepo LAzare
void relationWidget::deleteLines(){
    foreach(relationLine* item, m_lines){
        ((QWidget*)item->parent())->layout()->removeWidget(item);
        delete item;
    }
}
