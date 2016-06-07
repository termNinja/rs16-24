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
#include <QStackedLayout>
#include <cmath>
#include <moduleCodegen/memberfunction.hpp>
#include <moduleCodegen/membervariable.hpp>

using namespace codegen;

Q_DECLARE_METATYPE(MemberVisibility)

class ClassWidget : public QWidget
{
    Q_OBJECT
public:
    ClassWidget(QWidget *parent);
    ~ClassWidget()
    {};
    QString getName();

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
    void switchViews();
    void deleteWidget();
private slots:
    void memberFunctionParameterChanged();
private:
    QWidget *wClassWraper;
    QListWidget *qlwMembers;
    QPushButton *qpbAddMember;
    QListWidget *qlwMethods;
    QPushButton *qpbAddMethod;
    QLineEdit *qleClassName;


    QString name;
    QList<MemberFunction*> memberFuncions;
    QList<MemberVariable*> memberVariables;

    //used for moving
    QPoint offset;
    bool moving;
    bool resizing;
    int resizePosition;
    void getMemberFunctions();
    void getMembers();

    QWidget *makeCompactWidget();
    QWidget *makeFullSizeWidget();


QStackedLayout* stackedLayout;

};

#endif // CLASSWIDGET_HPP
