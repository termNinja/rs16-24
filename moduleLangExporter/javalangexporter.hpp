#ifndef JAVALANGEXPORTER_HPP
#define JAVALANGEXPORTER_HPP

#include <string>
#include "langexporter.hpp"
#include "moduleCodegen/membervariable.hpp"
#include "moduleCodegen/function.hpp"
#include "moduleCodegen/variable.hpp"
#include "moduleCodegen/class.hpp"

namespace lexp {

class JavaLangExporter : public LangExporter {
public:
	JavaLangExporter();

	std::string genBasicVariable(codegen::Variable &var) const;
	std::string genMemberVariable(codegen::MemberVariable &var) const;
	std::string genBasicFunction(codegen::Function &fun) const;
	std::string genMemberFunction(codegen::MemberFunction &fun) const;
	std::string genMemberConstructor(codegen::MemberConstructor &constructor, std::string className) const;
	std::string genClass(codegen::Class &cls) const;
	std::string genClassInclude(codegen::Class &cls) const;
	bool startCodeGeneration(codegen::Class &cls) const;

};

} // namespace end: lexp

#endif // JAVALANGEXPORTER_HPP
