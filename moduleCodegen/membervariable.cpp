#include "membervariable.hpp"
#include <iostream>

using namespace std;


namespace codegen {

MemberVariable::MemberVariable(Type type, std::string name, std::string owner, MemberVisibility visibility, bool isStatic)
	: Variable(type, name), m_owner(owner), m_visibility(visibility), m_isStatic(isStatic)
{
}

MemberVariable::MemberVariable()
{
}

std::string MemberVariable::getOwnerName() const
{
	return m_owner;
}

bool MemberVariable::isStatic() const
{
	return m_isStatic;
}

MemberVisibility MemberVariable::getVisibility() const
{
	return m_visibility;
}

void MemberVariable::setVisibility(MemberVisibility visibility)
{
	m_visibility = visibility;
}

void MemberVariable::setStatic(bool isStatic)
{
	m_isStatic = isStatic;
}

memberType MemberVariable::getMemberType() const
{
	return memberType::MEMBER_VARIABLE;
}

std::ostream &operator<<(std::ostream &out, const MemberVariable &mv)
{
	return out << mv.m_type <<  " "  << mv.m_owner << "::" << mv.m_name;
}

} // namespace end: codegen
