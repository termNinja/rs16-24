#include "membervariable.hpp"
#include <iostream>

using namespace std;


namespace codegen {

MemberVariable::MemberVariable(Type type, std::string name, std::string owner, MemberVisibility visibility)
	: Variable(type, name), m_owner(owner), m_visibility(visibility)
{
}

std::string MemberVariable::getOwnerName() const
{
	return m_owner;
}

MemberVisibility MemberVariable::getVisibility() const
{
	return m_visibility;
}

void MemberVariable::setVisibility(MemberVisibility visibility)
{
	m_visibility = visibility;
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
