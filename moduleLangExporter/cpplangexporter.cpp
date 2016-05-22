#include "cpplangexporter.hpp"

using std::string;

namespace lexp {

CppLangExporter::CppLangExporter()
{
}

string CppLangExporter::genBasicVariable(codegen::Variable var)
{
	string s;
	if (var.getType().isConst())
		s.append("const ");
	// TODO: is static?
	s.append(var.getType().getName() + " ");
	s.append(var.getName());
	return s;
}

string CppLangExporter::genMemberVariable(codegen::MemberVariable var, codegen::MemberVisibility v)
{
	string s;
	if (var.getType().isConst())
		s.append("const ");
	s.append(var.getType().getName() + " ");
	s.append(var.getName());
	return s;
}

string CppLangExporter::genBasicFunction(codegen::Function fun)
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

string CppLangExporter::genMemberFunction(codegen::MemberFunction fun, codegen::MemberVisibility v)
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
	s.append(")");
	if (fun.isConst())
		s.append(" const");
	s.append(";");
	return s;
}

string CppLangExporter::genClass(codegen::Class cls)
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
			s.append(genMemberFunction(a, codegen::MemberVisibility::PUBLIC) + "\n");
		}
		for (auto a : cls.getPublicMemberVariables()) {
			s.append(ind);
			s.append(genMemberVariable(a, codegen::MemberVisibility::PUBLIC) + ";\n");
		}

	}

	if (!cls.getProtectedMemberFunctions().empty() || !cls.getProtectedMemberVariables().empty()) {
		// write protected content
		s.append("\nprotected:\n");
		for (auto a : cls.getProtectedMemberFunctions()) {
			s.append(ind);
			s.append(genMemberFunction(a, codegen::MemberVisibility::PROTECTED) + "\n");
		}
		for (auto a : cls.getProtectedMemberVariables()) {
			s.append(ind);
			s.append(genMemberVariable(a, codegen::MemberVisibility::PROTECTED) + ";\n");
		}
	}

	if (!cls.getPrivateMemberFunctions().empty() || !cls.getPrivateMemberVariables().empty()) {
		// write private content
		s.append("\nprivate:\n");
		for (auto a : cls.getPrivateMemberFunctions()) {
			s.append(ind);
			s.append(genMemberFunction(a, codegen::MemberVisibility::PRIVATE) + "\n");
		}
		for (auto a : cls.getPrivateMemberVariables()) {
			s.append(ind);
			s.append(genMemberVariable(a, codegen::MemberVisibility::PRIVATE) + ";\n");
		}
	}


	s.append("};");
	return s;
}


} // namespace end: lexp
