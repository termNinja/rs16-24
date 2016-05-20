#include "mainwindow.h"
#include <QApplication>

#include <iostream>
#include <vector>
#include "moduleCodegen/type.hpp"
#include "moduleCodegen/variable.hpp"
#include "moduleCodegen/function.hpp"
#include "moduleCodegen/codegentester.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

	codegen::codegenTester tester;
	tester.peformTest();

	w.show();
	return a.exec();
}
