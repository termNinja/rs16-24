#ifndef CPPLANGEXPORTER_HPP
#define CPPLANGEXPORTER_HPP

#include <memory>
#include <string>
#include "langexporter.hpp"
#include "moduleCodegen/variable.hpp"
#include "moduleCodegen/membervariable.hpp"
#include "moduleCodegen/function.hpp"
#include "moduleCodegen/memberfunction.hpp"
#include "moduleCodegen/membervisibility.hpp"
#include "moduleCodegen/class.hpp"

namespace lexp {

class CppLangExporter : public LangExporter {
public:
	CppLangExporter();

	std::string genBasicVariable(codegen::Variable var) const;
	std::string genMemberVariable(codegen::MemberVariable var) const;
	std::string genBasicFunction(codegen::Function fun) const;
	std::string genMemberFunction(codegen::MemberFunction fun) const;
	std::string genClass(codegen::Class cls) const;

	bool startCodeGeneration(codegen::Class cls) const;
private:
};

} // namespace end: lexp

#endif // CPPLANGEXPORTER_HPP
