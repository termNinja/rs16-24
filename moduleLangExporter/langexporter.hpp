#ifndef LANGEXPORTER_HPP
#define LANGEXPORTER_HPP

#include <string>
#include <memory>
#include <cctype>
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

	virtual std::string genBasicVariable(codegen::Variable &var) const = 0;
	virtual std::string genMemberVariable(codegen::MemberVariable &var) const = 0;
	virtual std::string genBasicFunction(codegen::Function &fun) const = 0;
	virtual std::string genMemberFunction(codegen::MemberFunction &fun) const = 0;
	virtual std::string genMemberConstructor(codegen::MemberConstructor &constructor, std::string className) const = 0;
	virtual std::string genClassInclude(codegen::Class &cls) const = 0;
	virtual std::string genClass(codegen::Class &cls) const = 0;
	virtual bool startCodeGeneration(codegen::Class &cls) const = 0;

	std::string generateUpperCase(std::string s) const
	{
		std::string res = s;
		for (auto &c : res)
			if (isalpha(c))
				c = static_cast<char>(toupper(c));
		return res;
	}

	static std::string ind;
};

} // namespace end: lexp

#endif // LANGEXPORTER_HPP
