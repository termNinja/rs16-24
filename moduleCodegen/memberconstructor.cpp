#include "memberconstructor.hpp"

namespace codegen {

MemberConstructor::MemberConstructor(MemberVisibility visibility)
	: m_visibility(visibility)
{

}

MemberConstructor::MemberConstructor(std::string owner, MemberVisibility visibility)
	: m_owner(owner), m_visibility(visibility)
{
}


std::string MemberConstructor::getClassName() const
{
	return m_owner;
}

void MemberConstructor::setOwner(std::string owner)
{
	m_owner = owner;
}

MemberVisibility MemberConstructor::getVisibility() const
{
	return m_visibility;
}

void MemberConstructor::setVisibility(MemberVisibility visibility)
{
	m_visibility = visibility;
}

memberType MemberConstructor::getMemberType() const
{
	return memberType::MEMBER_CONSTRUCTOR;
}


} // namespace end: codegen
