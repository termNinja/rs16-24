#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QTableView>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QLayout>
#include <QLayoutItem>
#include "moduleAppController/resourcemanager.hpp"
#include "moduleLangExporter/cpplangexporter.hpp"

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


ClassWidget* MainWindow::getClass(){
   return allClassWidgets.at(0);
}

void MainWindow::on_pushButton_10_clicked()
{
    bool ok;
//    QString name = QInputDialog::getText(this, tr("Class name"),
//                                               tr("Input class name "), QLineEdit::Normal,
//                                               "class name", &ok);

    QWidget *parent  = ui->widget_2;
    ClassWidget* newClass = new ClassWidget(parent);
    allClassWidgets.push_back(newClass);
}

void QWidget::paintEvent(QPaintEvent *)
{

    QPainter painter(this);

    if(this->objectName().toStdString() == "widget_2")
    {
        QRectF rectangle(10.0, 20.0, 80.0, 60.0);
        int startAngle = 30 * 16;
        int spanAngle = 120 * 16;
        painter.drawArc(rectangle, startAngle, spanAngle);
    }

}


void MainWindow::on_pushButton_clicked()
{
//    bool ok;
//    QString name = QInputDialog::getText(this, tr("Class name"),
//                                               tr("Input class name "), QLineEdit::Normal,
    QWidget *parent  = ui->widget_2;
    update();
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

void MainWindow::on_pushButton_11_clicked()
{
    ClassWidget *clasa1 = allClassWidgets.at(0);
    ClassWidget *clasa2 = allClassWidgets.at(1);

    relationWidget r(ui->widget_2 , clasa1, clasa2, 2);

}

void MainWindow::GenerateCodeC(){
    foreach(ClassWidget* currentClass, allClassWidgets)
    {
        Class test = currentClass->getClass();
        lexp::CppLangExporter cppExporter;
        QMessageBox msgBox;
        msgBox.setText(QString::fromStdString(cppExporter.genClass(test)));
        msgBox.exec();
    }
}

void MainWindow::addRelationClicked(){

    qcbFirstClass = new QComboBox();
    qcbSecondClass = new QComboBox();
    foreach(ClassWidget* currentClassWidget, allClassWidgets){
        qcbFirstClass->addItem(currentClassWidget->getName());
        qcbSecondClass->addItem(currentClassWidget->getName());
    }

    qpbOk = new QPushButton("Make relation");
    connect(qpbOk, SIGNAL(clicked()), this , SLOT(makeRelation()));

    QLayout* ql = ((QWidget*)((QPushButton*)sender())->parent())->layout();
    ql->addWidget(qcbFirstClass);
    ql->addWidget(qcbSecondClass);
    ql->addWidget(qpbOk);

//    QMessageBox msgBox;
//    msgBox.setText("Test");
//    msgBox.exec();
}

void MainWindow::makeRelation(){
    ClassWidget *clasa1 = allClassWidgets.at(qcbFirstClass->currentIndex());
    ClassWidget *clasa2 = allClassWidgets.at(qcbSecondClass->currentIndex());

    relation r(ui->widget_2 , clasa1, clasa2);

    ((QWidget*)qcbFirstClass->parent())->layout()->removeWidget(qcbFirstClass);
    delete qcbFirstClass;
    delete qcbSecondClass;
    delete qpbOk;
}
