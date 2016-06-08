#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    QWidget *parent  = ui->scrollArea->widget();
    ClassWidget* newClass = new ClassWidget(parent);
    connect(newClass, SIGNAL(Moved()), this , SLOT(RefreshRelation()));
    connect(newClass, SIGNAL(Deleted()), this , SLOT(ClassWidgetDeleted()));
    allClassWidgets.push_back(newClass);
}

void MainWindow::on_pushButton_clicked()
{
//    bool ok;
//    QString name = QInputDialog::getText(this, tr("Class name"),
//                                               tr("Input class name "), QLineEdit::Normal,
    QWidget *parent  = ui->scrollArea->widget();
    update();
}

void MainWindow::GenerateCodeC()
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

	lexp::CppLangExporter cppExporter;

    bool codegenProcessSucceded= true;

    foreach(ClassWidget* currentClass, allClassWidgets)
    {
        currentClass->makeClass();
    }

    RelationManager *RelMen = RelationManager::instance();
    foreach(relationWidget* currentRelation, allRelationWidgets)
    {
        switch(currentRelation->getType()){
        case 0: RelMen->addAssociationRelation(currentRelation->getFirstClass()->getClass(),currentRelation->getSecondClass()->getClass()); break;
        case 1: RelMen->addInheritanceRelation(currentRelation->getFirstClass()->getClass(),currentRelation->getSecondClass()->getClass()); break;
        case 2: RelMen->addAggregationRelation(currentRelation->getFirstClass()->getClass(),currentRelation->getSecondClass()->getClass()); break;
        case 3: RelMen->addCompositionRelation(currentRelation->getFirstClass()->getClass(),currentRelation->getSecondClass()->getClass()); break;
        }

    }

    foreach(ClassWidget* currentClass, allClassWidgets)
    {
        Class* test = currentClass->getClass();
        bool codegenStatus = cppExporter.startCodeGeneration(*test);
		if (codegenStatus == false) {
			codegenProcessSucceded = false;

			// Report failed codegen proc
			QMessageBox msgBox;
            QString errMsg = "Class generation for " + QString::fromStdString(test->getName()) + " has failed.";
            errMsg.append("Generation of code was tried at " + rm->getProjectOutputPath());
            msgBox.setText(errMsg);
			msgBox.exec();
		}
    }


	if (codegenProcessSucceded) {
        QMessageBox msgBox;
        msgBox.setText("All classes were successfully generated");
		msgBox.exec();
	}
}


void MainWindow::generateCodeJava(){
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

    lexp::JavaLangExporter JavaExporter;

    bool codegenProcessSucceded= true;

    foreach(ClassWidget* currentClass, allClassWidgets)
    {
        currentClass->makeClass();
    }

    RelationManager *RelMen = RelationManager::instance();
    foreach(relationWidget* currentRelation, allRelationWidgets)
    {
        switch(currentRelation->getType()){
        case 0: RelMen->addAssociationRelation(currentRelation->getFirstClass()->getClass(),currentRelation->getSecondClass()->getClass()); break;
        case 1: RelMen->addInheritanceRelation(currentRelation->getFirstClass()->getClass(),currentRelation->getSecondClass()->getClass()); break;
        case 2: RelMen->addAggregationRelation(currentRelation->getFirstClass()->getClass(),currentRelation->getSecondClass()->getClass()); break;
        case 3: RelMen->addCompositionRelation(currentRelation->getFirstClass()->getClass(),currentRelation->getSecondClass()->getClass()); break;
        }

    }

    foreach(ClassWidget* currentClass, allClassWidgets)
    {
        Class* test = currentClass->getClass();
        bool codegenStatus = JavaExporter.startCodeGeneration(*test);
        if (codegenStatus == false) {
            codegenProcessSucceded = false;

            // Report failed codegen proc
            QMessageBox msgBox;
            QString errMsg = "Class generation for " + QString::fromStdString(test->getName()) + " has failed.";
            errMsg.append("Generation of code was tried at " + rm->getProjectOutputPath());
            msgBox.setText(errMsg);
            msgBox.exec();
        }
    }

    if (codegenProcessSucceded) {
        QMessageBox msgBox;
        msgBox.setText("All classes were successfully generated");
        msgBox.exec();
    }
}

void MainWindow::generateCodePhp(){
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

    lexp::PhpLangExporter phpExporter;

    bool codegenProcessSucceded= true;

    foreach(ClassWidget* currentClass, allClassWidgets)
    {
        currentClass->makeClass();
    }

    RelationManager *RelMen = RelationManager::instance();
    foreach(relationWidget* currentRelation, allRelationWidgets)
    {
        switch(currentRelation->getType()){
        case 0: RelMen->addAssociationRelation(currentRelation->getFirstClass()->getClass(),currentRelation->getSecondClass()->getClass()); break;
        case 1: RelMen->addInheritanceRelation(currentRelation->getFirstClass()->getClass(),currentRelation->getSecondClass()->getClass()); break;
        case 2: RelMen->addAggregationRelation(currentRelation->getFirstClass()->getClass(),currentRelation->getSecondClass()->getClass()); break;
        case 3: RelMen->addCompositionRelation(currentRelation->getFirstClass()->getClass(),currentRelation->getSecondClass()->getClass()); break;
        }

    }

    foreach(ClassWidget* currentClass, allClassWidgets)
    {
        Class* test = currentClass->getClass();
        bool codegenStatus = phpExporter.startCodeGeneration(*test);
        if (codegenStatus == false) {
            codegenProcessSucceded = false;

            // Report failed codegen proc
            QMessageBox msgBox;
            QString errMsg = "Class generation for " + QString::fromStdString(test->getName()) + " has failed.";
            errMsg.append("Generation of code was tried at " + rm->getProjectOutputPath());
            msgBox.setText(errMsg);
            msgBox.exec();
        }
    }

    if (codegenProcessSucceded) {
        QMessageBox msgBox;
        msgBox.setText("All classes were successfully generated");
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

    relationWidget* r = new relationWidget(ui->scrollArea->widget() , clasa1, clasa2,relationType);

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

    for(int j=0;j<allRelationWidgets.size();j++){
        relationWidget* item = allRelationWidgets.at(j);
//    foreach(relationWidget* item,allRelationWidgets){
        if(item->getFirstClass()== allClassWidgets.at(i) || item->getSecondClass()== allClassWidgets.at(i)){
//            QMessageBox msgBox;
//                msgBox.setText(QString::number(i));
//                msgBox.exec();
            item->refreshLines(ui->scrollArea->widget());
//            ui->widget_2->layout()->removeWidget(item);
//            item = new relationWidget(ui->widget_2,allClassWidgets.at(0),allClassWidgets.at(1),item->getType());
        }
    }


}

void MainWindow::on_pushButton_11_clicked()
{
    QWidget *parent  = ui->scrollArea->widget();
    interfaceWidget* newInterface = new interfaceWidget(parent);
    connect(newInterface, SIGNAL(Moved()), this , SLOT(RefreshRelation()));
    connect(newInterface, SIGNAL(Deleted()), this , SLOT(InterfaceWidgetDeleted()));

    allInterfaceWidgets.push_back(newInterface);
}


void MainWindow::ClassWidgetDeleted(){

    ClassWidget* classWidget = (ClassWidget*)sender();
    foreach(relationWidget* item, allRelationWidgets){
        if(item->getFirstClass()== classWidget || item->getSecondClass() == classWidget){

            item->deleteLines();
            item->deleteLater();
            allRelationWidgets.removeOne(item);
        }
    }
//    allClassWidgets.removeOne(classWidget);
//    QMessageBox msgBox;
//                    msgBox.setText(QString::number(allRelationWidgets.size()));
//                    msgBox.exec();
}

void MainWindow::InterfaceWidgetDeleted(){
//    QMessageBox msgBox;
//                    msgBox.setText("Test");
//                    msgBox.exec();
}
