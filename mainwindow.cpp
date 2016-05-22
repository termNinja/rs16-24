#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QTableView>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QLayout>
#include <QLayoutItem>

//TODO: 1. Napraviti klasu "classWidget"  koja ce sluziti za uml objekta Klase
//      2. Napraviti da "classWidget" lepo izgleda
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_10_clicked()
{
    QWidget *parent  = ui->widget_2;

    //set color to widget so its easy to see dimensions
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::red);
    parent->setAutoFillBackground(true);
    parent->setPalette(Pal);

    //if we need to set maximum size to layout we need to put it in a widget
    //TODO: is there better way to do it?
    QWidget *wClassWraper = new QWidget(parent);
    wClassWraper->setMaximumWidth(200);
    Pal.setColor(QPalette::Background, Qt::blue);
    wClassWraper->setAutoFillBackground(true);
    wClassWraper->setPalette(Pal);

    QVBoxLayout *vblClass = new QVBoxLayout(wClassWraper);
    wClassWraper->setLayout(vblClass);


    //listview for member variables, lMembersModel is used as data source for lvMembers.
    QListView *lvMembers = new QListView();
    vblClass->addWidget(lvMembers);
    lMembersModel = new QStandardItemModel();
    lvMembers->setMaximumHeight(100);

    //creating button for adding members
    QPushButton *btnAddMember = new QPushButton("Add member variable");
    vblClass->addWidget(btnAddMember);
    QObject::connect(btnAddMember, SIGNAL(clicked()),this, SLOT(addMemberClicked()));

    //creating second half of a classObject(methods listview and button), same as the first half
    QListView *lvMethods = new QListView();
    vblClass->addWidget(lvMethods);
    lMethodsModel = new QStandardItemModel();
    lvMethods->setMaximumHeight(100);

    QPushButton *btnAddMethod = new QPushButton("Add method");
    vblClass->addWidget(btnAddMethod);
    QObject::connect(btnAddMethod, SIGNAL(clicked()),this, SLOT(addMethodClicked()));

    //because widget is visible we need to call show() method to see newly added objects
    wClassWraper->show();
    parent->show();

}

void MainWindow::on_pushButton_clicked()
{
    QWidget *parent  = ui->widget;

    QPushButton *button1 = new QPushButton(parent);
    button1->setText("test");
}

void MainWindow::addMemberClicked()
{
    QVBoxLayout *qbl =(QVBoxLayout*)(((QPushButton*)sender())->parentWidget()->layout());
    QListView *qlv = ((QListView*)(qbl->itemAt(0)->widget()));

    QStandardItem* Items = new QStandardItem("new member");
    lMembersModel->appendRow(Items);

    qlv->setModel(lMembersModel);
}

void MainWindow::addMethodClicked()
{
    QVBoxLayout *qbl =(QVBoxLayout*)(((QPushButton*)sender())->parentWidget()->layout());
    QListView *qlv = ((QListView*)(qbl->itemAt(2)->widget()));

    QStandardItem* Items = new QStandardItem("new method");
    lMethodsModel->appendRow(Items);
    qlv->setModel(lMethodsModel);
}


