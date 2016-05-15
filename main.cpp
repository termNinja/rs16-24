#include "mainwindow.h"
#include <QApplication>

#include <iostream>
#include <vector>
#include "moduleCodegen/type.hpp"
#include "moduleCodegen/variable.hpp"
#include "moduleCodegen/function.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

	// TESTING CODE

	// Type test
    //Type type(QString("double"), true);
//	std::cout << type << std::endl;

	// Variable test
    //Variable var(type, QString("x"));
    //std::cout << var << std::endl;

	// Function test
    //std::vector<Variable> params;
    //params.push_back(var);
    //params.push_back(Variable(Type(QString("QString")), QString("y")));
    //Function fun(type, QString("calculate"), params);
    //std::cout << fun << std::endl;

	w.show();
	return a.exec();
}
