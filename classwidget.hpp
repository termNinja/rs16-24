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
#include <QComboBox>
#include <QHoverEvent>
#include <cmath>
#include <moduleCodegen/memberfunction.hpp>
#include <moduleCodegen/membervariable.hpp>

using namespace codegen;

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
    bool insideRect(QPoint mousePos);
    void hoverMove(QHoverEvent * event);
    bool event(QEvent *e);
    void moveClass(QMouseEvent *e);
    QPoint mousePoint;

public slots:
    void addMemberClicked();
    void addMethodClicked();
    void removeMethodClicked();

    void removeMemberClicked();
    void lineEditTextChanged();

    void addMethodParameterClicked();
private:
    QWidget *wClassWraper;
    QVBoxLayout *qvblClass;
    QListWidget *qlwMembers;
    QPushButton *qpbAddMember;
    QListWidget *qlwMethods;
    QPushButton *qpbAddMethod;
    QLineEdit *qleClassName;

    QList<MemberFunction*> memberFuncions;
    QList<MemberVariable*> memberVariables;

    //used for moving
    QPoint offset;
    bool moving;
    bool m_resize;
    void getMemberFunctions();
    void getMembers();
};

#endif // CLASSWIDGET_HPP
