#include "relation.hpp"


relation::relation(QWidget *parent ,ClassWidget *class1, ClassWidget *class2){

    std::vector<QPoint> pointsOfClass1 = getFourPoints(class1->pos() , class1->width() , class1->height());
    std::vector<QPoint> pointsOfClass2 = getFourPoints(class2->pos() , class2->width() , class2->height());
    std::vector<QPoint> minDistTwoPoints = minDist(pointsOfClass1 , pointsOfClass2);



    //relationLine *l = new relationLine(parent ,p1 , p2 );
    //relationLine *l1 = new relationLine(parent ,p3 , p1 );

}

int relation::numberOfLines(QPoint p1, QPoint p2 ){
    return 2;
}

std::vector<QPoint> relation::getFourPoints(QPoint pos , int width , int height){
    std::vector<QPoint> vector;
    int x = pos.x();
    int y = pos.y();
    //left edge point
    vector.push_back(QPoint( x ,  (height/2) - y ));
    //bottom edge point
    vector.push_back(QPoint( x + (width/2) , y + height ));
    //right edge point
    vector.push_back(QPoint( x + width , (height/2) - y ));
    //top edge point
    vector.push_back(QPoint( x + (width/2) , y ));

    return vector;
}

std::vector<QPoint> relation::minDist(std::vector<QPoint> &class1 , std::vector<QPoint> &class2){

    //pair iz indexes of point cooridnates in vector
//    std::map<std::pair<int,int> , int > mapOfDiff;
//    mapOfDiff[std::make_pair(1 , 3)] = 2;
    int positionClass1=0;
    int positionClass2=0;
    std::vector<QPoint> returnValue;

    std::vector<QPoint>::iterator iter1 = class1.begin();
    std::vector<QPoint>::iterator iter2 = class1.begin();
    int i=0;
    int j=0;
    double minDist = 0;


    for ( ; iter1 < class1.end() ; iter1++ , i++) {
        for ( ; iter2 < class2.end() ; iter2++ , j++) {
              QPoint first = class1.at(i);
              QPoint second = class2.at(i);
              int tmpMinDist = sqrt(pow(first.x() - second.x() , 2) + pow(first.y() - second.y(),2));
              if(tmpMinDist < minDist)
              {
                positionClass1 = i;
                positionClass2 = j;
                minDist = tmpMinDist;
              }
        }
    }
    returnValue.push_back(class1.at(positionClass1));
    returnValue.push_back(class2.at(positionClass2));

    return returnValue;
}
