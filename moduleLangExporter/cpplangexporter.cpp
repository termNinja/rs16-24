#include <fstream>
#include <iostream>
#include <QDir>
#include "cpplangexporter.hpp"
#include "moduleAppController/resourcemanager.hpp"
#include "moduleCodegen/relationmanager.hpp"

using std::string;

namespace lexp {

CppLangExporter::CppLangExporter()
{
}

string CppLangExporter::genBasicVariable(codegen::Variable &var) const
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

string CppLangExporter::genMemberVariable(codegen::MemberVariable &var) const
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

string CppLangExporter::genBasicFunction(codegen::Function &fun) const
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

string CppLangExporter::genMemberFunction(codegen::MemberFunction &fun) const
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
	if (! funParams.empty()) {
		for (unsigned i = 0; i < fun.getNumberOfParameters()-1; ++i)
			s.append(genBasicVariable(funParams[i]) + ", ");
		s.append(genBasicVariable(funParams.back()));
	}
	s.append(")");
	if (fun.isConst())
		s.append(" const");
	s.append(";");
	return s;
}


string CppLangExporter::genMemberConstructor(codegen::MemberConstructor &constructor) const
{
	string s;

	s.append(constructor.getClassName());
	s.append(genConstructorBody(constructor));
	return s;
}

string CppLangExporter::genMemberConstructor(codegen::MemberConstructor &constructor, string className) const
{
	string s;
	s.append(className);
	s.append(genConstructorBody(constructor));
	return s;
}

string CppLangExporter::genConstructorBody(codegen::MemberConstructor &constructor) const
{
	string s;
	s.append("(");
	auto funParams = constructor.getParameters();
	if (! funParams.empty()) {
		for (unsigned i = 0; i < constructor.getNumberOfParameters()-1; ++i)
			s.append(genBasicVariable(funParams[i]) + ", ");
		s.append(genBasicVariable(funParams.back()));
	}
	s.append(");");
	return s;
}


string CppLangExporter::genClass(codegen::Class &cls) const
{
	string s;
	string ind = LangExporter::ind;
	unsigned magicConstLineBreak = 4;

	s.append(genClassInclude(cls));

	s.append("class " + cls.getName());

	// Handling inheritance
	std::vector<const codegen::Class*> inherits = cls.getClassesThatClassInherits();
	if (! inherits.empty()) {
		unsigned i;
		s.append(" : ");
		for (i = 0; i < inherits.size()-1; ++i) {
			if (i % magicConstLineBreak == 0) {
				s.append("\n" + ind);
			}
			// for now, public only
			s.append("public " + inherits[i]->getName() + ", ");
		}
		s.append("public " + inherits[i]->getName());

	}


	s.append(" {\n");

	// Class body

	if (!cls.getPublicMemberFunctions().empty()
		|| !cls.getPublicMemberVariables().empty() || !cls.getPublicConstructors().empty()) {
		// write public content
		s.append("public:\n");
		for (auto &a : cls.getPublicConstructors()) {
			s.append(ind);
			s.append(genMemberConstructor(a, cls.getName()) + "\n");
		}
		for (auto &a : cls.getPublicMemberFunctions()) {
			s.append(ind);
			s.append(genMemberFunction(a) + "\n");
		}
		for (auto &a : cls.getPublicMemberVariables()) {
			s.append(ind);
			s.append(genMemberVariable(a) + ";\n");
		}

	}

	if (!cls.getProtectedMemberFunctions().empty() || !cls.getProtectedMemberVariables().empty()) {
		// write protected content
		s.append("\nprotected:\n");
		for (auto &a : cls.getProtectedConstructors()) {
			s.append(ind);
			s.append(genMemberConstructor(a, cls.getName()) + "\n");
		}
		for (auto &a : cls.getProtectedMemberFunctions()) {
			s.append(ind);
			s.append(genMemberFunction(a) + "\n");
		}
		for (auto &a : cls.getProtectedMemberVariables()) {
			s.append(ind);
			s.append(genMemberVariable(a) + ";\n");
		}
	}

	if (!cls.getPrivateMemberFunctions().empty() || !cls.getPrivateMemberVariables().empty()) {
		// write private content
		s.append("\nprivate:\n");
		for (auto &a : cls.getPrivateConstructors()) {
			s.append(ind);
			s.append(genMemberConstructor(a, cls.getName()) + "\n");
		}
		for (auto &a : cls.getPrivateMemberFunctions()) {
			s.append(ind);
			s.append(genMemberFunction(a) + "\n");
		}
		for (auto &a : cls.getPrivateMemberVariables()) {
			s.append(ind);
			s.append(genMemberVariable(a) + ";\n");
		}
	}


	s.append("};");
	return s;
}

string CppLangExporter::genClassInclude(codegen::Class &cls) const
{
	string res;

	codegen::RelationManager *rm = codegen::RelationManager::instance();
	std::set<const codegen::Class*> relatedClasses = rm->getAllClassesThatUseGivenClass(&cls);

	for (auto c : relatedClasses) {
		res.append("#include \"");
		res.append(c->getName() + ".hpp\"\n");
	}

	return res.append("\n");
}

bool CppLangExporter::startCodeGeneration(codegen::Class &cls) const
{
	app::ResourceManager *rm = &app::ResourceManager::instance();
	string outputPath = rm->getProjectOutputPath().toStdString();
	string outputFilePath = outputPath + rm->getPlatformSeparator() + cls.getName() + ".hpp";
	std::ofstream outputFile(outputFilePath);

	// For testing purposes
	// outputPath = "";
	// outputFilePath = cls.getName() + ".hpp";

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
