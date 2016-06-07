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
#include "relation.hpp"

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
    void on_choose_dir_clicked();
    void on_pushButton_11_clicked();

    void GenerateCodeC();

protected:
    ClassWidget* getClass();

private:
    Ui::MainWindow *ui;
    QList<ClassWidget*> allClassWidgets;
};

#endif // MAINWINDOW_H
