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
    QDir().mkdir(pathTONewDir);
}
