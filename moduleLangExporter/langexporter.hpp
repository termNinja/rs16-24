#ifndef LANGEXPORTER_HPP
#define LANGEXPORTER_HPP

#include <string>
#include <memory>
#include "moduleCodegen/variable.hpp"
#include "moduleCodegen/membervariable.hpp"
#include "moduleCodegen/function.hpp"
#include "moduleCodegen/memberfunction.hpp"
#include "moduleCodegen/membervisibility.hpp"
#include "moduleCodegen/class.hpp"

namespace lexp {

class LangExporter {
public:
	LangExporter();
	virtual ~LangExporter();

	virtual std::string genBasicVariable(codegen::Variable var) = 0;
	virtual std::string genMemberVariable(codegen::MemberVariable var, codegen::MemberVisibility v) = 0;
	virtual std::string genBasicFunction(codegen::Function fun) = 0;
	virtual std::string genMemberFunction(codegen::MemberFunction fun, codegen::MemberVisibility v) = 0;
	virtual std::string genClass(codegen::Class cls) = 0;

	static std::string ind;
};

} // namespace end: lexp

#endif // LANGEXPORTER_HPP
