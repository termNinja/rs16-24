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
#include <QInputDialog>
#include <QListWidget>

class ClassWidget : public QWidget
{
    Q_OBJECT
public:
    ClassWidget(QWidget *parent);
    ~ClassWidget()
    {};

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    QPoint mousePoint;

public slots:
    void addMemberClicked();
    void addMethodClicked();


private:
    QWidget *wClassWraper;
    QVBoxLayout *vblClass;
    QListWidget *lvMembers;
    QPushButton *btnAddMember;
    QListWidget *lvMethods;
    QPushButton *btnAddMethod;
    QStandardItemModel* lMembersModel;
    QStandardItemModel* lMethodsModel;
    QLineEdit *lclassName;

    //used for moving
    QPoint offset;
    bool moving;
};

#endif // CLASSWIDGET_HPP
