#ifndef INTERFACEWIDGET_H
#define INTERFACEWIDGET_H

#include<iostream>
#include <QLineEdit>
#include <QListWidget>
#include <QStackedLayout>
#include <QWidget>
#include <QComboBox>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QStandardItem>
#include<QHoverEvent>
#include <cmath>
#include <moduleCodegen/membervariable.hpp>
#include <moduleCodegen/memberfunction.hpp>
#include <moduleCodegen/membervisibility.hpp>

using namespace codegen;

class interfaceWidget : public QWidget
{
    Q_OBJECT
public:
    explicit interfaceWidget(QWidget *parent = 0);

    QString getName();
protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    bool insideRect(QPoint mousePos);
    void hoverMove(QHoverEvent * event);
    bool event(QEvent *e);
    void moveInterface(QMouseEvent *e);
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
    void lineEditRenameInterface();

private:

    QLineEdit* qleInterfaceName;
    QListWidget* qlwMembers;
    QListWidget* qlwMethods;

    QString name;
    QList<MemberVariable> memberVariables;
    QList<MemberFunction> memberFuncions;


    //used for moving
    QPoint offset;
    bool moving;
    bool resizing;
    int resizePosition;
    void getMemberFunctions();
    void getMemberVariables();

    QWidget *makeCompactWidget();
    QWidget *makeFullSizeWidget();

    QStackedLayout* stackedLayout;

signals:
       void Moved();
       void Deleted();
};

#endif // INTERFACEWIDGET_H
