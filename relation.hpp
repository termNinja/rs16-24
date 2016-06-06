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

class relation
{
public:
    relation(QWidget *parent , ClassWidget *class1,  ClassWidget *class2);
protected:
    int numberOfLines(QPoint p1, QPoint p2 );
    std::vector<QPoint> getFourPoints(QPoint pos , int width , int height);
    std::vector<QPoint> minDist(std::vector<QPoint> &class1 , std::vector<QPoint> &class2);

private:
    std::vector<relationLine> m_lines;
};

#endif // RELATION_HPP
