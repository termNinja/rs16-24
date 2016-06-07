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
    connect(newClass, SIGNAL(Moved()), this , SLOT(RefreshRelation()));
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

void MainWindow::GenerateCodeC()
{
	lexp::CppLangExporter cppExporter;
	app::ResourceManager* rm = &app::ResourceManager::instance();
	bool codegenProcessSucceded= true;

    foreach(ClassWidget* currentClass, allClassWidgets)
    {
        Class test = currentClass->getClass();
		bool codegenStatus = cppExporter.startCodeGeneration(test);
		if (codegenStatus == false) {
			codegenProcessSucceded = false;

			// Report failed codegen proc
			QMessageBox msgBox;
			std::string errMsg = "Class generation for " + test.getName() + " has failed.";
			errMsg.append("Generation of code was tried at " + rm->getProjectOutputPath().toStdString());
			msgBox.setText(QString::fromStdString(errMsg));
			msgBox.exec();
		}
    }

	if (codegenProcessSucceded) {
		QMessageBox msgBox;
		std::string msg = "All classes were successfully generated";
		msgBox.setText(QString::fromStdString(msg));
		msgBox.exec();
	}
}

void MainWindow::addRelationClicked(){

    QLayout* ql = ((QWidget*)((QPushButton*)sender())->parent())->layout();

    if(ql->count()>5){
        delete qcbFirstClass;
        delete qcbSecondClass;
         delete qpbOk;
    }

    qcbFirstClass = new QComboBox();
    qcbSecondClass = new QComboBox();
    foreach(ClassWidget* currentClassWidget, allClassWidgets){
        qcbFirstClass->addItem(currentClassWidget->getName());
        qcbSecondClass->addItem(currentClassWidget->getName());
    }

    qpbOk = new QPushButton("Make relation");
    connect(qpbOk, SIGNAL(clicked()), this , SLOT(makeRelation()));


    ql->addWidget(qcbFirstClass);
    ql->addWidget(qcbSecondClass);
    ql->addWidget(qpbOk);

    relationType = ql->indexOf((QPushButton*)sender());
//    QMessageBox msgBox;
//    msgBox.setText("Test");
//    msgBox.exec();
}

void MainWindow::makeRelation(){
    ClassWidget *clasa1 = allClassWidgets.at(qcbFirstClass->currentIndex());
    ClassWidget *clasa2 = allClassWidgets.at(qcbSecondClass->currentIndex());

    relationWidget* r = new relationWidget(ui->widget_2 , clasa1, clasa2,relationType);

    allRelationWidgets.push_back(r);
    ((QWidget*)qcbFirstClass->parent())->layout()->removeWidget(qcbFirstClass);
    delete qcbFirstClass;
    delete qcbSecondClass;
    delete qpbOk;
}


void MainWindow::on_toolBox_currentChanged(int index)
{

    if(((QToolBox*)sender())->widget(1)->children().at(0)->children().count()>5){
        delete qcbFirstClass;
        delete qcbSecondClass;
         delete qpbOk;
    }
}

void MainWindow::RefreshRelation(){
    int i = allClassWidgets.indexOf((ClassWidget*)sender());

    foreach(relationWidget* item,allRelationWidgets){
        if(item->getFirstClass()== allClassWidgets.at(i) || item->getSecondClass()== allClassWidgets.at(i)){
//            QMessageBox msgBox;
//                msgBox.setText(QString::number(i));
//                msgBox.exec();
            item->deleteLines();
            item = new relationWidget(ui->widget_2,item->getFirstClass(),item->getSecondClass(),item->getType());
        }
    }


}
