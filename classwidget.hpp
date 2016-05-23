#ifndef CLASSWIDGET_HPP
#define CLASSWIDGET_HPP

#include <iostream>
#include <QPushButton>
#include <QMessageBox>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QListView>
#include <QStandardItem>
#include <QPalette>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QPoint>
#include <QLabel>

class ClassWidget : public QWidget
{
    Q_OBJECT
public:
    ClassWidget(QWidget *parent  , QStandardItemModel* lMembersModel,   QStandardItemModel* lMethodsModel , QString name);
    bool pressed;
    ~ClassWidget()
    {};

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    QPoint mousePoint;

public slots:
    void addMemberClicked();
    void addMethodClicked();


private:
    QWidget *wClassWraper;
    QVBoxLayout *vblClass;
    QListView *lvMembers;
    QPushButton *btnAddMember;
    QListView *lvMethods;
    QPushButton *btnAddMethod;
    QStandardItemModel* lMembersModel;
    QStandardItemModel* lMethodsModel;
    QLabel *lclassName;
};

#endif // CLASSWIDGET_HPP
