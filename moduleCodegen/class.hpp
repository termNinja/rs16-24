#ifndef CLASS_HPP
#define CLASS_HPP

#include <string>
#include <vector>
#include "type.hpp"
#include "membervariable.hpp"
#include "memberfunction.hpp"

namespace codegen {

class Class {
public:
	Class(std::string name);
	Class(std::string className, std::vector<MemberFunction> memberFunctions);
	Class(std::string className, std::vector<MemberVariable> memberVariables);
	Class(std::string className, std::vector<MemberFunction> memberFunctions, std::vector<MemberVariable> memberVariables);

	Class(
			std::string name,
			std::vector<MemberFunction> pubMemFun,
			std::vector<MemberFunction> privMemFun,
			std::vector<MemberFunction> protMemFun,
			std::vector<MemberVariable> pubMemVar,
			std::vector<MemberVariable> privMemVar,
			std::vector<MemberVariable> protMemVar
	);

	std::vector<MemberFunction>& getPublicMemberFunctions();
	std::vector<MemberFunction>& getPrivateMemberFunctions();
	std::vector<MemberFunction>& getProtectedMemberFunctions();
	std::vector<MemberVariable>& getPublicMemberVariables();
	std::vector<MemberVariable>& getPrivateMemberVariables();
	std::vector<MemberVariable>& getProtectedMemberVariables();

	std::string getName() const;

	friend std::ostream& operator<<(std::ostream& out, const Class &c);

private:
	std::string m_name;
	std::vector<MemberFunction> m_pubMemFun;
	std::vector<MemberFunction> m_privMemFun;
	std::vector<MemberFunction> m_protMemFun;
	std::vector<MemberVariable> m_pubMemVar;
	std::vector<MemberVariable> m_privMemVar;
	std::vector<MemberVariable> m_protMemVar;

	void filterMemberFunctions(std::vector<MemberFunction> memberFunctions);
	void filterMemberVariables(std::vector<MemberVariable> memberVariables);


};

} // namespace end: codegen

#endif // CLASS_HPP
