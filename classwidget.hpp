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
    void removeMethodClicked();

    void removeMemberClicked();
    void lineEditTextChanged();
private:
    QWidget *wClassWraper;
    QVBoxLayout *vblClass;
    QListWidget *lvMembers;
    QPushButton *btnAddMember;
    QListWidget *lvMethods;
    QPushButton *btnAddMethod;
    QLineEdit *lclassName;

    //used for moving
    QPoint offset;
    bool moving;
};

#endif // CLASSWIDGET_HPP
