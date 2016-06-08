#include <fstream>
#include <set>
#include "javalangexporter.hpp"
#include "moduleCodegen/membervisibility.hpp"
#include "moduleCodegen/relationmanager.hpp"
#include "moduleAppController/resourcemanager.hpp"

using std::string;

namespace lexp {

JavaLangExporter::JavaLangExporter()
{

}

string JavaLangExporter::genBasicVariable(codegen::Variable &var) const
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

string JavaLangExporter::genMemberVariable(codegen::MemberVariable &var) const
{
	string s;
	s.append(codegen::getVisibilityAsString(var.getVisibility()) + " ");
	if (var.isStatic())
		s.append("static ");

	if (var.getType().isConst())
		s.append("final ");

	s.append(var.getType().getName() + " ");
	s.append(var.getName());
	return s;
}

string JavaLangExporter::genBasicFunction(codegen::Function &fun) const
{
	string s;
	if (fun.getReturnType().isConst())
		s.append("final ");

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

string JavaLangExporter::genMemberFunction(codegen::MemberFunction &fun) const
{
	string s;

	s.append(codegen::getVisibilityAsString(fun.getVisibility()) + " ");

	if (fun.isStatic())
		s.append("static ");

	if (fun.getReturnType().isConst())
		s.append("final ");

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

// Haha java doesn't have this :D
//	if (fun.isConst())
//		s.append(" const");
	s.append(";");
	return s;
}

string JavaLangExporter::genMemberConstructor(codegen::MemberConstructor &constructor, std::string className) const
{
	string s;
	s.append(className);
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

string JavaLangExporter::genClass(codegen::Class &cls) const
{
	string s;
	string ind = LangExporter::ind;

	s.append(genClassInclude(cls));

	s.append("public class " + cls.getName());

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

string JavaLangExporter::genClassInclude(codegen::Class &cls) const
{
	string res;

	codegen::RelationManager *rm = codegen::RelationManager::instance();
	std::set<const codegen::Class*> relatedClasses = rm->getAllClassesThatUseGivenClass(&cls);

	for (auto c : relatedClasses) {
		res.append("import ");
		res.append(c->getName() + ";\n");
	}

	return res.append("\n");
}

bool JavaLangExporter::startCodeGeneration(codegen::Class &cls) const
{
	app::ResourceManager *rm = &app::ResourceManager::instance();
	string outputPath = rm->getProjectOutputPath().toStdString();
	string outputFilePath = outputPath + rm->getPlatformSeparator() + cls.getName() + ".java";
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
