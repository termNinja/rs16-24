#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QListView>
#include <QStandardItem>
#include <QDir>
#include <QFileDialog>
#include <QDir>
#include "classwidget.hpp"
#include <QInputDialog>
#include <QPainter>
#include <QWidget>
#include <QLabel>
#include "relationline.hpp"
#include <vector>
#include <iostream>
#include <QTableView>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QLayout>
#include <QLayoutItem>
#include "moduleAppController/resourcemanager.hpp"
#include "moduleLangExporter/cpplangexporter.hpp"
#include "moduleLangExporter/javalangexporter.hpp"
#include "relationwidget.hpp"
#include "interfacewidget.hpp"
#include "moduleCodegen/relationmanager.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_10_clicked();
    void on_pushButton_clicked();

    void GenerateCodeC();

    void addRelationClicked();
    void makeRelation();
    void on_toolBox_currentChanged(int index);

    void RefreshRelation();
    void on_pushButton_11_clicked();

    void ClassWidgetDeleted();
    void InterfaceWidgetDeleted();
    void generateCodeJava();
    void generateCodePhp();
protected:
    ClassWidget* getClass();

private:
    Ui::MainWindow *ui;
    QList<ClassWidget*> allClassWidgets;
    QList<relationWidget*> allRelationWidgets;
    QList<interfaceWidget*> allInterfaceWidgets;

    QComboBox* qcbFirstClass;
    QComboBox* qcbSecondClass;
    QPushButton* qpbOk;
    int relationType;
    std::set<Class *> getClasses();
};

#endif // MAINWINDOW_H
