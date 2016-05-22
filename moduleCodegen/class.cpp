#include "class.hpp"
#include <iostream>

using namespace std;

namespace codegen {

Class::Class(QString name, std::vector<MemberFunction> pubMemFun,
			 std::vector<MemberFunction> privMemFun,
			 std::vector<MemberFunction> protMemFun,
			 std::vector<MemberVariable> pubMemVar,
			 std::vector<MemberVariable> privMemVar,
			 std::vector<MemberVariable> protMemVar)
	: m_name(name), m_pubMemFun(pubMemFun), m_privMemFun(privMemFun), m_protMemFun(protMemFun),
	  m_pubMemVar(pubMemVar), m_privMemVar(privMemVar), m_protMemVar(protMemVar)
{
}

Class::Class(QString name, std::vector<MemberFunction> pubMemFun, std::vector<MemberVariable> privMemVar)
	: m_name(name), m_pubMemFun(pubMemFun), m_privMemVar(privMemVar)
{
}

std::vector<MemberFunction> &Class::getPublicMemberFunctions()
{
	return m_pubMemFun;
}

std::vector<MemberFunction> &Class::getPrivateMemberFunctions()
{
	return m_privMemFun;
}

std::vector<MemberFunction> &Class::getProtectedMemberFunctions()
{
	return m_protMemFun;
}

std::vector<MemberVariable> &Class::getPublicMemberVariables()
{
	return m_pubMemVar;
}

std::vector<MemberVariable> &Class::getPrivateMemberVariables()
{
	return m_privMemVar;
}

std::vector<MemberVariable> &Class::getProtectedMemberVariables()
{
	return m_protMemVar;
}

QString Class::getName() const
{
	return m_name;
}

std::ostream &operator<<(std::ostream &out, const Class &c)
{
	std::string sep = "    ";
	out << "class " << c.m_name.toStdString() << " {\n";

	if (!c.m_pubMemFun.empty() || !c.m_pubMemVar.empty()) {
		// write public content
		out << "public:\n";
		for (auto a : c.m_pubMemFun) out << sep << a << "\n";
		for (auto a : c.m_pubMemVar) out << sep << a << "\n";
	}

	if (!c.m_protMemFun.empty() || !c.m_protMemVar.empty()) {
		// write protected content
		out << "protected:\n";
		for (auto a : c.m_protMemFun) out << sep << a << "\n";
		for (auto a : c.m_protMemVar) out << sep << a << "\n";
	}

	if (!c.m_privMemFun.empty() || !c.m_privMemVar.empty()) {
		// write private content
		out << "private:\n";
		for (auto a : c.m_privMemFun) out << sep << a << "\n";
		for (auto a : c.m_privMemVar) out << sep << a << "\n";
	}

	// close down class
	out << "};";
	return out;
}

} // namespace end: codegen
