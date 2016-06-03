#include "memberfunction.hpp"
#include <iostream>

using namespace std;


namespace codegen {

MemberFunction::MemberFunction(string functionName, bool isConst, MemberVisibility visibility)
	: Function(functionName), m_isConst(isConst), m_visibility(visibility)
{
}

MemberFunction::MemberFunction(codegen::Type returnType, std::string functionName,
	const std::vector<codegen::Variable> &parameters, std::string owner, bool isConst, MemberVisibility visibility)
	: Function(returnType, functionName, parameters), m_owner(owner), m_isConst(isConst), m_visibility(visibility)
{
}

std::string MemberFunction::getOwnerName() const
{
	return m_owner;
}

void MemberFunction::setOwner(std::string className)
{
	m_owner = className;
}

bool MemberFunction::isConst() const
{
	return m_isConst;
}

MemberVisibility MemberFunction::getVisibility() const
{
	return m_visibility;
}

void MemberFunction::setVisibility(MemberVisibility visibility)
{
	m_visibility = visibility;
}

std::ostream &operator<<(std::ostream &out, const MemberFunction &function)
{
	out << function.m_returnType << " " << function.m_owner
		<< "::" << function.m_name << "(";
	for (unsigned i = 0; i < function.m_parameters.size()-1; ++i)
		out << function.m_parameters[i] << ", ";
	out << function.m_parameters.back() << ")";
	return out;
}

} // namespace end: codegen
