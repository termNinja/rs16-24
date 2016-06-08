#include <string>
#include "phplangexporter.hpp"
#include "moduleCodegen/membervisibility.hpp"
#include "moduleCodegen/relationmanager.hpp"
#include "moduleAppController/appcontrollertester.hpp"

using std::string;

namespace lexp {

PhpLangExporter::PhpLangExporter()
{

}

string lexp::PhpLangExporter::genBasicVariable(codegen::Variable &var) const
{
	return "$" + var.getName();
}

string PhpLangExporter::genMemberVariable(codegen::MemberVariable &var) const
{
	return codegen::getVisibilityAsString(var.getVisibility()) + " " + genBasicVariable(var);
}

string PhpLangExporter::genBasicFunction(codegen::Function &fun) const
{
	string s;

	s.append("function ");
	s.append(fun.getName());
	s.append("(");

	auto funParams = fun.getParameters();
	if (! funParams.empty()) {
		for (unsigned i = 0; i < fun.getNumberOfParameters()-1; ++i)
			s.append(genBasicVariable(funParams[i]) + ", ");
		s.append(genBasicVariable(funParams.back()));
	}
	s.append(");");

	return s;

}

string PhpLangExporter::genMemberFunction(codegen::MemberFunction &fun) const
{
	string s;

	if (fun.isStatic())
		s.append("static ");

	s.append(codegen::getVisibilityAsString(fun.getVisibility()));
	s.append(" function ");
	s.append(fun.getName() + "(");

	auto funParams = fun.getParameters();
	if (! funParams.empty()) {
		for (unsigned i = 0; i < fun.getNumberOfParameters()-1; ++i)
			s.append(genBasicVariable(funParams[i]) + ", ");
		s.append(genBasicVariable(funParams.back()));
	}
	s.append(");");
	return s;
}

string PhpLangExporter::genMemberConstructor(codegen::MemberConstructor &constructor, string className) const
{
	string s;

	s.append("function __construct");
	auto funParams = constructor.getParameters();
	if (! funParams.empty()) {
		for (unsigned i = 0; i < constructor.getNumberOfParameters()-1; ++i)
			s.append(genBasicVariable(funParams[i]) + ", ");
		s.append(genBasicVariable(funParams.back()));
	}
	s.append(");");

	return s;
}

string PhpLangExporter::genClassInclude(codegen::Class &cls) const
{
	string s;

	codegen::RelationManager *rm = codegen::RelationManager::instance();
	std::set<const codegen::Class*> relatedClasses = rm->getAllClassesThatUseGivenClass(&cls);

	for (auto c : relatedClasses) {
		s.append("include_once(");
		s.append(c->getName() + ".php\")\n");
	}

	return s.append("\n");

}

string PhpLangExporter::genClass(codegen::Class &cls) const
{
	string s;
	string ind = LangExporter::ind;

	s.append("<?php\n");

	s.append(genClassInclude(cls));

	s.append("class " + cls.getName());

	// Handling inheritance
	std::vector<const codegen::Class*> inherits = cls.getClassesThatClassInherits();
	if (! inherits.empty()) {
		unsigned i;
		s.append(" extends ");
		for (i = 0; i < inherits.size()-1; ++i) {
			if (i == 1) {
				std::cerr << "Multiple inheritance not supported in java!" << std::endl;
				break;
			}

			// for now, public only
			s.append(inherits[i]->getName());
		}

	} else {
		std::cout << "Received empty inheritance vector while generating code for class " << cls.getName() << std::endl;
	}


	s.append(" {\n");

	// Class body

	if (!cls.getPublicMemberFunctions().empty()
		|| !cls.getPublicMemberVariables().empty() || !cls.getPublicConstructors().empty()) {
		// write public content
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
		s.append("\n");
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
		s.append("\n");
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

	s.append("}");


	return s;
}

bool PhpLangExporter::startCodeGeneration(codegen::Class &cls) const
{
	app::ResourceManager *rm = &app::ResourceManager::instance();
	string outputPath = rm->getProjectOutputPath().toStdString();
	string outputFilePath = outputPath + rm->getPlatformSeparator() + cls.getName() + ".php";
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
