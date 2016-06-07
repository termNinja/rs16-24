#ifndef RELATIONLINE_HPP
#define RELATIONLINE_HPP

#include <QPainter>
#include <QPoint>
#include <QLabel>
#include <QStylePainter>

//TODO: add types of relation
// 0 <- association (blue)
// 1 <- inheritance (red)
// 2 <- aggregation (green)
// 3 <- composition (black)

class relationLine : QLabel
{
public:
    relationLine(QWidget *parent , QPoint first , QPoint second , int type);

protected:
    int verticalOrHorizontal(QPoint p1, QPoint p2);

private:
    QPoint m_first;
    QPoint m_second;
};

#endif // RELATIONLINE_HPP
