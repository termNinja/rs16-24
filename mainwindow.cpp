#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QTableView>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QLayout>
#include <QLayoutItem>
#include "moduleAppController/resourcemanager.hpp"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    window()->showMaximized();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_10_clicked()
{
    bool ok;
//    QString name = QInputDialog::getText(this, tr("Class name"),
//                                               tr("Input class name "), QLineEdit::Normal,
//                                               "class name", &ok);

    QWidget *parent  = ui->widget_2;
    ClassWidget *w = new ClassWidget(parent);
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

	// Setting output path for resource manager
	app::ResourceManager *rm = &app::ResourceManager::instance();
	rm->setProjectPath(pathTONewDir);

    QDir().mkdir(pathTONewDir);
}
