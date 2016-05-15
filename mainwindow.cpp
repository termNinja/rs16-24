#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QTableView>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QLayout>
#include <QLayoutItem>

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

    QVBoxLayout *vbox = new QVBoxLayout;
    QPushButton *button1 = new QPushButton("One");
    vbox->addWidget(button1);
    button1->setGeometry(QRect(QPoint(100, 100),QSize(200, 300)));
    ui->groupBox->setLayout(vbox);

}
