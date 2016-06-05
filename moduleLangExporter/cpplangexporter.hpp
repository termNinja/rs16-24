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
#include "moduleCodegen/memberconstructor.hpp"
#include "moduleCodegen/class.hpp"

namespace lexp {

/**
 * @brief The CppLangExporter class that enables generation of c++ from codegen library.
 */
class CppLangExporter : public LangExporter {
public:
	/**
	 *  \brief Constructor for class.
	 */
	CppLangExporter();

	/**
	 * @brief Generates c++ code for a basic variable object.
	 * @param var Variable object that's getting generated.
	 * @return Returns c++ code that represents a given variable.
	 */
	std::string genBasicVariable(codegen::Variable &var) const;

	/**
	 * @brief Generates c++ code for a basic member variable object.
	 * @param var Member Variable object that's getting generated.
	 * @return Returns c++ code that represents a given member variable.
	 */
	std::string genMemberVariable(codegen::MemberVariable &var) const;

	/**
	 * @brief Generates c++ code for a function object.
	 * @param fun Function object that's getting generated.
	 * @return Returns c++ code that represents a function signature.
	 */
	std::string genBasicFunction(codegen::Function &fun) const;

	/**
	 * @brief Generates c++ code for a member function object.
	 * @param fun Member function object that's getting generated.
	 * @return Returns c++ code that represents member function's signature.
	 */
	std::string genMemberFunction(codegen::MemberFunction &fun) const;

	/**
	 * @brief Generates c++ code for a constructor object.
	 * @param constructor Constructor object that's getting generated.
	 * @return Returns c++ code that represents constructor's signature.
	 */
	std::string genMemberConstructor(codegen::MemberConstructor &constructor) const;

	/**
	 * @brief Generates c++ code for a class object.
	 * @param cls Class that's getting generated.
	 * @return Returns c++ code that represents a whole class.
	 */
	std::string genClass(codegen::Class &cls) const;


	/**
	 * @brief Stars code generation and saves output to path given by resource manager.
	 * @param cls Class that's getting generated.
	 * @return Returns true if code generation was successful.
	 */
	bool startCodeGeneration(codegen::Class cls) const;
private:
};

} // namespace end: lexp

#endif // CPPLANGEXPORTER_HPP
