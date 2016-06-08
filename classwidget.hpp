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
#include <moduleCodegen/class.hpp>
#include <moduleCodegen/membervisibility.hpp>

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

    Class* getClass();

    void makeClass();
protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    bool insideRect(QPoint mousePos);
    void hoverMove(QHoverEvent * event);
    bool event(QEvent *e);
    void moveClass(QMouseEvent *e);
    QPoint mousePoint;


private slots:
    void addMemberClicked();
    void addMethodClicked();
    void removeMethodClicked();

    void removeMemberClicked();
    void lineEditTextChanged();

    void addMethodParameterClicked();
    void switchViews();
    void deleteWidget();

    void ParameterChanged();
    void lineEditRenameClass();

    void removeConstructorClicked();
    void addConstructorClicked();
    void addConstructorParameterClicked();
private:

    QLineEdit* qleClassName;
    QListWidget* qlwMembers;
    QListWidget* qlwMethods;
    QListWidget* qlwConstructors;

    QString name;
    QList<MemberVariable> memberVariables;
    QList<MemberConstructor> memberConstructors;
    QList<MemberFunction> memberFuncions;


    //used for moving
    QPoint offset;
    bool moving;
    bool resizing;
    int resizePosition;
    void getMemberFunctions();
    void getMemberVariables();
    void getMemberConstructors();

    QWidget *makeCompactWidget();
    QWidget *makeFullSizeWidget();

    QStackedLayout* stackedLayout;

    Class* myClass;
signals:
       void Moved();
       void Deleted();
};

#endif // CLASSWIDGET_HPP
