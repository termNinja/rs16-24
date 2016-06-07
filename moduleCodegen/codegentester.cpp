#include "codegentester.hpp"
#include "moduleAppController/resourcemanager.hpp"
#include "moduleLangExporter/cpplangexporter.hpp"
#include "moduleCodegen/member.hpp"
#include "relationmanager.hpp"

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

	// polymorphism test
	std::vector<Member*> members;
	MemberVariable *polyMemVar = new MemberVariable(Type("double"), "x");
	members.push_back(polyMemVar);

	MemberConstructor *polyCon = new MemberConstructor("PolyClass");
	members.push_back(polyCon);
	members.push_back(new MemberFunction(Type("double"), "PolyTest")); // private by default
	Class polyClass("PolyClass", members);

	// ------------------------------------------------------------------------
	// Class generation test
	// ------------------------------------------------------------------------
	lexp::CppLangExporter cppExporter;
	std::cout << cppExporter.genClass(c) << std::endl;
	// cppExporter.startCodeGeneration(c);

	std::cerr << "Beginning class PolyClass generation..." << std::endl;
	std::cout << cppExporter.genClass(polyClass) << std::endl;

	// ------------------------------------------------------------------------
	// Relation manager test
	// ------------------------------------------------------------------------
	std::cout << "Relation manager test: " << std::endl;
	RelationManager *rm = RelationManager::instance();
	rm->addInheritanceRelation(&polyClass, &c);
	rm->addInheritanceRelation(&c, &polyClass);
	rm->addAssociationRelation(&polyClass, &c);
	Class includeTester1 = Class("includeTester1");
	Class includeTester2 = Class("includeTester2");
	Class includeTester3 = Class("includeTester3");
	Class includeTester4 = Class("includeTester4");
	rm->addInheritanceRelation(&includeTester1, &polyClass);
	rm->addAssociationRelation(&polyClass, &includeTester1);
	rm->addAggregationRelation(&polyClass, &includeTester2);
	rm->addCompositionRelation(&polyClass, &includeTester3);
	std::cout << *rm << std::endl;
	std::cout << cppExporter.genClass(polyClass) << std::endl;
}

} // namespace end: codegen
