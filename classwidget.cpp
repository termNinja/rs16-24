#include "classwidget.hpp"
#include <iostream>

ClassWidget::ClassWidget(QWidget *parent , QStandardItemModel* lMembersModel,
                         QStandardItemModel* lMethodsModel , QString name ){

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
    lclassName = new QLabel(name);
    lclassName->setMaximumWidth(200);
    Pal.setColor(QPalette::Background, Qt::white);
    lclassName->setAutoFillBackground(true);
    lclassName->setPalette(Pal);
    lclassName->setAlignment(Qt::AlignCenter);
    vblClass->addWidget(lclassName);

    //listview for member variables, lMembersModel is used as data source for lvMembers.
    lvMembers = new QListWidget();
    vblClass->addWidget(lvMembers);
    lMembersModel = new QStandardItemModel();
    lvMembers->setMaximumHeight(100);

    //creating button for adding members
    btnAddMember = new QPushButton("Add member variable");
    vblClass->addWidget(btnAddMember);
    QObject::connect(btnAddMember, SIGNAL(clicked()), this , SLOT(addMemberClicked()));

    //creating second half of a classObject(methods listview and button), same as the first half
    lvMethods = new QListWidget();
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

void ClassWidget::mousePressEvent(QMouseEvent *e)
{


}



void ClassWidget::addMemberClicked()
{
    bool ok;
    QString member = QInputDialog::getText(this, tr("Add member"),
                                               tr("Add member"), QLineEdit::Normal,
                                               "member", &ok);
    lvMembers->addItem(member);
}

void ClassWidget::addMethodClicked()
{
    bool ok;
    QString method = QInputDialog::getText(this, tr("Add method"),
                                               tr("Add method"), QLineEdit::Normal,
                                               "method", &ok);
    lvMethods->addItem(method.append("(").append(")"));
}

void ClassWidget::mouseReleaseEvent(QMouseEvent *e)
{
    pressed = false;
}

void ClassWidget::mouseMoveEvent(QMouseEvent *e)
{
    if(pressed == true)
    {
       mousePoint =  e->globalPos();
        move( mousePoint);
    }
}
