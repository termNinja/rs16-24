#include "codegentester.hpp"

namespace codegen {

/// Overloaded operator << is just for logging and testing purposes.
/// True mapping for given language shall be done by a completely different module

void codegenTester::peformTest() {

	// Type test
	Type type(QString("double"), true);
	std::cout << type << std::endl;

	// Variable test
	Variable var(type, QString("x"));
	std::cout << var << std::endl;

	// Function test
	std::vector<Variable> params;
	params.push_back(var);
	params.push_back(Variable(Type(QString("QString")), QString("y")));
	Function fun(type, QString("calculate"), params);
	std::cout << fun << std::endl;

	// Member Variable test
	MemberVariable mvariable(type, QString("simpleVariable"), QString("NumericLib"));
	std::cout << mvariable << std::endl;

	// Member function test
	MemberFunction mfunction(type, QString("calculate"), params, QString("NumericLib"));
	std::cout << mfunction << std::endl;

	// ------------------------------------------------------------------------
	// Class test
	// ------------------------------------------------------------------------
	std::cout << std::endl;

	// construct member functions
	MemberFunction mf1(type, QString("helloWorld"), params, QString("NumericLib"));
	Variable v1(Type(QString("double")), QString("x"));
	Variable v2(Type(QString("double")), QString("y"));
	std::vector<Variable> mf2Params;
	mf2Params.push_back(v1);
	mf2Params.push_back(v2);
	MemberFunction mf2(type, QString("euclidianDistance"), mf2Params, QString("NumericLib"));
	std::vector<MemberFunction> numLibFunctions;
	numLibFunctions.push_back(mf1);
	numLibFunctions.push_back(mf2);

	// construct member variables
	MemberVariable mv1(type, QString("x"), QString("NumericLib"));
	MemberVariable mv2(type, QString("y"), QString("NumericLib"));
	std::vector<MemberVariable> numLibMemberVars;
	numLibMemberVars.push_back(mv1);
	numLibMemberVars.push_back(mv2);
	Class c(
		QString("NumericLib"),
		numLibFunctions,
		numLibMemberVars
	);
	std::cout << c << std::endl;
}

} // namespace end: codegen
