#include "classwidget.hpp"
#include <iostream>

classwidget::classwidget(QWidget *parent , QStandardItemModel* lMembersModel,   QStandardItemModel* lMethodsModel ){

    pressed = false;
    //set color to widget so its easy to see dimensions
    QPalette Pal(palette());
    //Pal.setColor(QPalette::Background, Qt::red);
    //parent->setAutoFillBackground(true);
    parent->setPalette(Pal);

    //if we need to set maximum size to layout we need to put it in a widget
    //TODO: is there better way to do it?
    wClassWraper = new QWidget(parent);
    wClassWraper->setMaximumWidth(200);
    Pal.setColor(QPalette::Background, Qt::black);
    wClassWraper->setAutoFillBackground(true);
    wClassWraper->setPalette(Pal);
    vblClass = new QVBoxLayout(wClassWraper);
    wClassWraper->setLayout(vblClass);

    //add class name
    lclassName = new QLabel("Name of class");
    lclassName->setMaximumWidth(200);
    Pal.setColor(QPalette::Background, Qt::white);
    lclassName->setAutoFillBackground(true);
    lclassName->setPalette(Pal);
    lclassName->setAlignment(Qt::AlignCenter);
    vblClass->addWidget(lclassName);

    //listview for member variables, lMembersModel is used as data source for lvMembers.
    lvMembers = new QListView();
    vblClass->addWidget(lvMembers);
    lMembersModel = new QStandardItemModel();
    lvMembers->setMaximumHeight(100);

    //creating button for adding members
    btnAddMember = new QPushButton("Add member variable");
    vblClass->addWidget(btnAddMember);
    QObject::connect(btnAddMember, SIGNAL(clicked()), this , SLOT(addMemberClicked()));

    //creating second half of a classObject(methods listview and button), same as the first half
    lvMethods = new QListView();
    vblClass->addWidget(lvMethods);
    lMethodsModel = new QStandardItemModel();
    lvMethods->setMaximumHeight(100);

    btnAddMethod = new QPushButton("Add method");
    vblClass->addWidget(btnAddMethod);
    QObject::connect(btnAddMethod, SIGNAL(clicked()) , this , SLOT(addMethodClicked()));

    //because widget is visible we need to call show() method to see newly added objects
    wClassWraper->show();
    parent->show();
}



void classwidget::addMemberClicked()
{
//    QVBoxLayout *qbl =(QVBoxLayout*)(((QPushButton*)sender())->parentWidget()->layout());
//    QListView *qlv = ((QListView*)(qbl->itemAt(0)->widget()));

//    QStandardItem* Items = new QStandardItem("new member");
//    lMembersModel->appendRow(Items);

//    qlv->setModel(lMembersModel);
}

void classwidget::addMethodClicked()
{
//    QVBoxLayout *qbl =(QVBoxLayout*)(((QPushButton*)sender())->parentWidget()->layout());
//    QListView *qlv = ((QListView*)(qbl->itemAt(2)->widget()));

//    QStandardItem* Items = new QStandardItem("new method");
//    lMethodsModel->appendRow(Items);
//    qlv->setModel(lMethodsModel);
}

void classwidget::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton){
        pressed = true;
    }
}

void classwidget::mouseReleaseEvent(QMouseEvent *e)
{
    pressed = false;
}

void classwidget::mouseMoveEvent(QMouseEvent *e)
{
    if(pressed == true)
    {
       mousePoint =  e->globalPos();
        move( mousePoint);
    }
}
