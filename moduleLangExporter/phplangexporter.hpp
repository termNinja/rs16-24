#ifndef PHPLANGEXPORTER_HPP
#define PHPLANGEXPORTER_HPP

#include "langexporter.hpp"

namespace lexp {

class PhpLangExporter : public LangExporter {
public:
	PhpLangExporter();

	std::string genBasicVariable(codegen::Variable &var) const;
	std::string genMemberVariable(codegen::MemberVariable &var) const;
	std::string genBasicFunction(codegen::Function &fun) const;
	std::string genMemberFunction(codegen::MemberFunction &fun) const;
	std::string genMemberConstructor(codegen::MemberConstructor &constructor, std::string className) const;
	std::string genClassInclude(codegen::Class &cls) const;
	std::string genClass(codegen::Class &cls) const;
	bool startCodeGeneration(codegen::Class &cls) const;

};

} // namespace end: lexp

#endif // PHPLANGEXPORTER_HPP
