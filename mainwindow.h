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


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
