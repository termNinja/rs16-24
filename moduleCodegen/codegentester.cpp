#include "codegentester.hpp"
namespace codegen {

void codegenTester::peformTest() {

	// xType test
	Type type(QString("double"), true);
	std::cout << type << std::endl;

	// xVariable test
	Variable var(type, QString("x"));
	std::cout << var << std::endl;

	// xFunction test
	std::vector<Variable> params;
	params.push_back(var);
	params.push_back(Variable(Type(QString("QString")), QString("y")));
	Function fun(type, QString("calculate"), params);
	std::cout << fun << std::endl;

}

}
