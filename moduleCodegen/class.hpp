#ifndef CLASS_HPP
#define CLASS_HPP

#include <string>
#include <vector>
#include "type.hpp"
#include "membervariable.hpp"
#include "memberfunction.hpp"
#include "memberconstructor.hpp"

namespace codegen {

class Class {
public:
	Class(std::string name);

	// NOTE: Going to get removed in newer versions
	Class(std::string className, std::vector<MemberFunction> memberFunctions);

	// NOTE: Going to get removed in newer versions
	Class(std::string className, std::vector<MemberVariable> memberVariables);

	// NOTE: Going to get removed in newer versions
	Class(std::string className, std::vector<MemberFunction> memberFunctions, std::vector<MemberVariable> memberVariables);

	// MAIN constructor
	Class(std::string className,
		  std::vector<MemberConstructor> memberConstructors,
		  std::vector<MemberFunction> memberFunctions,
		  std::vector<MemberVariable> memberVariables);

	// NOTE: Going to get removed in newer versions
	Class(
			std::string name,
			std::vector<MemberFunction> pubMemFun,
			std::vector<MemberFunction> privMemFun,
			std::vector<MemberFunction> protMemFun,
			std::vector<MemberVariable> pubMemVar,
			std::vector<MemberVariable> privMemVar,
			std::vector<MemberVariable> protMemVar
	);

	// These getters allow you to add new members into class
	// because they return vectors by reference
	std::vector<MemberFunction>& getPublicMemberFunctions();
	std::vector<MemberFunction>& getPrivateMemberFunctions();
	std::vector<MemberFunction>& getProtectedMemberFunctions();
	std::vector<MemberVariable>& getPublicMemberVariables();
	std::vector<MemberVariable>& getPrivateMemberVariables();
	std::vector<MemberVariable>& getProtectedMemberVariables();
	std::vector<MemberConstructor>& getPublicConstructors();
	std::vector<MemberConstructor>& getPrivateConstructors();
	std::vector<MemberConstructor>& getProtectedConstructors();

	void addConstructor(MemberConstructor &c);

	std::string getName() const;
	void setName(std::string name);

	friend std::ostream& operator<<(std::ostream& out, const Class &c);

private:
	std::string m_name;
	std::vector<MemberFunction> m_pubMemFun;
	std::vector<MemberFunction> m_privMemFun;
	std::vector<MemberFunction> m_protMemFun;
	std::vector<MemberVariable> m_pubMemVar;
	std::vector<MemberVariable> m_privMemVar;
	std::vector<MemberVariable> m_protMemVar;
	std::vector<MemberConstructor> m_pubConst;
	std::vector<MemberConstructor> m_privConst;
	std::vector<MemberConstructor> m_protConst;

	void filterMemberFunctions(std::vector<MemberFunction> memberFunctions);
	void filterMemberVariables(std::vector<MemberVariable> memberVariables);
	void filterMemberConstructors(std::vector<MemberConstructor> memberConstuctors);

};

} // namespace end: codegen

#endif // CLASS_HPP
