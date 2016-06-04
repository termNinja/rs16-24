#include "codegentester.hpp"
#include "moduleAppController/resourcemanager.hpp"
#include "moduleLangExporter/cpplangexporter.hpp"

namespace codegen {

/// Overloaded operator << is just for logging and testing purposes.
/// True mapping for given language shall be done by a completely different module

void codegenTester::peformTest() {
	std::cout << "CODEGEN TEST:" << std::endl;

	// Type test
	Type type("double", true);
	std::cout << type << std::endl;

	// Variable test
	Variable var(type, "x");
	std::cout << var << std::endl;

	// Function test
	std::vector<Variable> params;
	params.push_back(var);
	params.push_back(Variable(Type("QString"), "y"));
	Function fun(type, "calculate", params);
	std::cout << fun << std::endl;

	// Member Variable test
	MemberVariable mvariable(type, "simpleVariable", "NumericLib");
	std::cout << mvariable << std::endl;

	// Member function test
	MemberFunction mfunction(type, "calculate", params, "NumericLib");
	std::cout << mfunction << std::endl;

	// ------------------------------------------------------------------------
	// Class test
	// ------------------------------------------------------------------------
	std::cout << std::endl;

	// construct member functions
	MemberFunction mf1(type, "helloWorld", params, "NumericLib");
	Variable v1(Type("double"), "x");
	Variable v2(Type("double"), "y");
	std::vector<Variable> mf2Params;
	mf2Params.push_back(v1);
	mf2Params.push_back(v2);
	MemberFunction mf2(type, "euclidianDistance", mf2Params, "NumericLib");
	std::vector<MemberFunction> numLibFunctions;
	numLibFunctions.push_back(mf1);
	numLibFunctions.push_back(mf2);

	// construct member variables
	MemberVariable mv1(type, "x", "NumericLib");
	MemberVariable mv2(type, "y", "NumericLib");
	std::vector<MemberVariable> numLibMemberVars;
	numLibMemberVars.push_back(mv1);
	numLibMemberVars.push_back(mv2);

	// construct constructors (using constructors lol)
	MemberConstructor con1("NumericLib");
	con1.addParameter(v1);

	MemberConstructor con2("NumericLib");
	con2.addParameter(v1);
	con2.addParameter(v2);

	std::vector<MemberConstructor> numLibConstructors;
	numLibConstructors.push_back(con1);
	numLibConstructors.push_back(con2);


	Class c(
		"NumericLib",
		numLibConstructors,
		numLibFunctions,
		numLibMemberVars
	);
	std::cout << c << std::endl;

	// ------------------------------------------------------------------------
	// Class generation test
	// ------------------------------------------------------------------------
	lexp::CppLangExporter cppExporter;
	std::cout << cppExporter.genClass(c) << std::endl;
	cppExporter.startCodeGeneration(c);
}

} // namespace end: codegen
