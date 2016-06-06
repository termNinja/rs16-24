#ifndef RELATIONLINE_HPP
#define RELATIONLINE_HPP

#include <QPainter>
#include <QPoint>
#include <QLabel>
#include <QStylePainter>


class relationLine : QLabel
{
public:
    relationLine(QWidget *parent , QPoint first , QPoint second);

protected:
    int verticalOrHorizontal(QPoint p1, QPoint p2);

private:
    QPoint m_first;
    QPoint m_second;
};

#endif // RELATIONLINE_HPP
