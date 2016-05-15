#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QListView>
#include<QStandardItem>

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

    void addMemberClicked();

    void addMethodClicked();


private:
    Ui::MainWindow *ui;
    //just for testing
    QStandardItemModel* lMembersModel;
    QStandardItemModel* lMethodsModel;
};

#endif // MAINWINDOW_H
