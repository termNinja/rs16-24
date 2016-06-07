#ifndef RELATION_HPP
#define RELATION_HPP

#include <iostream>
#include <vector>
#include <QPoint>
#include <map>
#include <tuple>
#include <cmath>
#include "relationline.hpp"
#include "classwidget.hpp"


//TODO ADD TYPES enum
//typedef enum TYPES { association = 0 , inheritance = 1 };

class relationWidget
{

public:
    relationWidget(QWidget *parent , ClassWidget *class1,  ClassWidget *class2 , int type);

protected:
    int numberOfLines(QPoint p1, QPoint p2 );
    std::vector<QPoint> getFourPoints(QPoint pos , int width , int height);
    std::vector<QPoint> minDist(std::vector<QPoint> &class1 , std::vector<QPoint> &class2);
    void makeRelation(QWidget *parent , std::vector<QPoint> minDistTwoPoints , int type
                      ,ClassWidget *class1, ClassWidget *class2);


private:
    std::vector<relationLine> m_lines;
    int m_firstClassPointPosition;
    int m_secondClassPointPosition;
    int m_type;
};

#endif // RELATION_HPP
