#ifndef CLASS_HPP
#define CLASS_HPP

#include <QString>
#include <vector>
#include "type.hpp"
#include "membervariable.hpp"
#include "memberfunction.hpp"

namespace codegen {

class Class {
public:
	Class(QString name);

	Class(
			QString name,
			std::vector<MemberFunction> pubMemFun,
			std::vector<MemberFunction> privMemFun,
			std::vector<MemberFunction> protMemFun,
			std::vector<MemberVariable> pubMemVar,
			std::vector<MemberVariable> privMemVar,
			std::vector<MemberVariable> protMemVar
	);

	// Very commonly used construction
	Class(
			QString name,
			std::vector<MemberFunction> pubMemFun,
			std::vector<MemberVariable> privMemVar

	);

	std::vector<MemberFunction>& getPublicMemberFunctions();
	std::vector<MemberFunction>& getPrivateMemberFunctions();
	std::vector<MemberFunction>& getProtectedMemberFunctions();
	std::vector<MemberVariable>& getPublicMemberVariables();
	std::vector<MemberVariable>& getPrivateMemberVariables();
	std::vector<MemberVariable>& getProtectedMemberVariables();

	QString getName() const;

	friend std::ostream& operator<<(std::ostream& out, const Class &c);

private:
	QString m_name;
	std::vector<MemberFunction> m_pubMemFun;
	std::vector<MemberFunction> m_privMemFun;
	std::vector<MemberFunction> m_protMemFun;
	std::vector<MemberVariable> m_pubMemVar;
	std::vector<MemberVariable> m_privMemVar;
	std::vector<MemberVariable> m_protMemVar;

};

} // namespace end: codegen

#endif // CLASS_HPP
