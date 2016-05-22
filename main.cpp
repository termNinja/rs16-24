#include "mainwindow.h"
#include <QApplication>

#include <iostream>
#include <vector>
#include "moduleCodegen/type.hpp"
#include "moduleCodegen/variable.hpp"
#include "moduleCodegen/function.hpp"
#include "moduleCodegen/codegentester.hpp"
#include "moduleAppController/appcontrollertester.hpp"

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    MainWindow w;

	codegen::codegenTester codegenTester;
	app::AppControllerTester appControllerTester;

	std::cout << "======================================================" << std::endl;
	codegenTester.peformTest();
	std::cout << "======================================================" << std::endl;
	appControllerTester.performTest();
	std::cout << "======================================================" << std::endl;

//	w.show();
//	return a.exec();
}
