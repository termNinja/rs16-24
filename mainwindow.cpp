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
    QWidget *parent  = ui->widget_2;
    classwidget *w = new classwidget(parent , lMembersModel , lMethodsModel);
}

void MainWindow::on_pushButton_clicked()
{
    QWidget *parent  = ui->widget;

    QPushButton *button1 = new QPushButton(parent);
    button1->setText("test");
}



void MainWindow::on_choose_dir_clicked()
{
    QString path = QFileDialog::getExistingDirectory(
                  this,
                  tr("Please pick your directory to save code."),
                  "/home",
                  QFileDialog::ShowDirsOnly);

    QString pathTONewDir = path + "/SourceCode";
    QDir().mkdir(pathTONewDir);
}
