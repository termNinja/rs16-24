#include "cpplangexporter.hpp"
#include "moduleAppController/resourcemanager.hpp"
#include <fstream>
#include <iostream>

using std::string;

namespace lexp {

CppLangExporter::CppLangExporter()
{
}

string CppLangExporter::genBasicVariable(codegen::Variable var) const
{
	string s;
	if (var.isStatic())
		s.append("static ");

	if (var.getType().isConst())
		s.append("const ");
	s.append(var.getType().getName() + " ");
	s.append(var.getName());
	return s;
}

string CppLangExporter::genMemberVariable(codegen::MemberVariable var) const
{
	string s;
	if (var.isStatic())
		s.append("static ");

	if (var.getType().isConst())
		s.append("const ");

	s.append(var.getType().getName() + " ");
	s.append(var.getName());
	return s;
}

string CppLangExporter::genBasicFunction(codegen::Function fun) const
{
	string s;
	if (fun.getReturnType().isConst())
		s.append("const ");

	s.append(fun.getReturnType().getName() + " ");
	s.append(fun.getName());
	s.append("(");

	auto funParams = fun.getParameters();
	for (unsigned i = 0; i < fun.getNumberOfParameters()-1; ++i)
		s.append(genBasicVariable(funParams[i]) + ", ");
	s.append(genBasicVariable(funParams.back()));
	s.append(");");

	return s;
}

string CppLangExporter::genMemberFunction(codegen::MemberFunction fun) const
{
	string s;

	if (fun.isStatic())
		s.append("static ");

	if (fun.getReturnType().isConst())
		s.append("const ");

	s.append(fun.getReturnType().getName() + " ");
	s.append(fun.getName());
	s.append("(");

	auto funParams = fun.getParameters();
	for (unsigned i = 0; i < fun.getNumberOfParameters()-1; ++i)
		s.append(genBasicVariable(funParams[i]) + ", ");
	s.append(genBasicVariable(funParams.back()));
	s.append(")");
	if (fun.isConst())
		s.append(" const");
	s.append(";");
	return s;
}

string CppLangExporter::genClass(codegen::Class cls) const
{
	string s;
	string ind = LangExporter::ind;
	s.append("class " + cls.getName());
	// TODO: Extends?
	s.append(" {\n");

	if (!cls.getPublicMemberFunctions().empty() || !cls.getPublicMemberVariables().empty()) {
		// write public content
		s.append("public:\n");
		for (auto a : cls.getPublicMemberFunctions()) {
			s.append(ind);
			s.append(genMemberFunction(a) + "\n");
		}
		for (auto a : cls.getPublicMemberVariables()) {
			s.append(ind);
			s.append(genMemberVariable(a) + ";\n");
		}

	}

	if (!cls.getProtectedMemberFunctions().empty() || !cls.getProtectedMemberVariables().empty()) {
		// write protected content
		s.append("\nprotected:\n");
		for (auto a : cls.getProtectedMemberFunctions()) {
			s.append(ind);
			s.append(genMemberFunction(a) + "\n");
		}
		for (auto a : cls.getProtectedMemberVariables()) {
			s.append(ind);
			s.append(genMemberVariable(a) + ";\n");
		}
	}

	if (!cls.getPrivateMemberFunctions().empty() || !cls.getPrivateMemberVariables().empty()) {
		// write private content
		s.append("\nprivate:\n");
		for (auto a : cls.getPrivateMemberFunctions()) {
			s.append(ind);
			s.append(genMemberFunction(a) + "\n");
		}
		for (auto a : cls.getPrivateMemberVariables()) {
			s.append(ind);
			s.append(genMemberVariable(a) + ";\n");
		}
	}


	s.append("};");
	return s;
}

bool CppLangExporter::startCodeGeneration(codegen::Class cls) const
{
	app::ResourceManager *rm = &app::ResourceManager::instance();
	string outputPath = rm->getProjectOutputPath().toStdString();

	std::ofstream outputFile(outputPath);
	string generatedClass = genClass(cls);
	if (outputFile << generatedClass) {
		std::cout << "Successfully generated code for class " << cls.getName() << std::endl;
		std::cout << "Code saved at: " << outputPath << std::endl;
		return true;
	} else {
		std::cerr << "Failed generating code for class " << cls.getName() << std::endl;
		std::cerr << "Attempted writing to: " << outputPath << std::endl;
		return false;
	}
}


} // namespace end: lexp
