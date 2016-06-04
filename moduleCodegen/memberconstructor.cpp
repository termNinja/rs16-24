#include "memberconstructor.hpp"
#include "type.hpp"

namespace codegen {

MemberConstructor::MemberConstructor(MemberVisibility visibility)
	: m_visibility(visibility)
{

}

MemberConstructor::MemberConstructor(std::string owner, MemberVisibility visibility)
	: Function(owner), m_owner(owner), m_visibility(visibility)
{
}

MemberConstructor::MemberConstructor(std::vector<Variable> &parameters,
									 std::string owner, MemberVisibility visibility)
	: Function(Type("void"), owner, parameters), m_owner(owner), m_visibility(visibility)
{
}


std::string MemberConstructor::getClassName() const
{
	return m_owner;
}

void MemberConstructor::setOwner(std::string owner)
{
	m_owner = owner;
	m_name = owner;
}

MemberVisibility MemberConstructor::getVisibility() const
{
	return m_visibility;
}

void MemberConstructor::setVisibility(MemberVisibility visibility)
{
	m_visibility = visibility;
}

void MemberConstructor::addParameter(Variable var)
{
	m_parameters.push_back(var);
}

memberType MemberConstructor::getMemberType() const
{
	return memberType::MEMBER_CONSTRUCTOR;
}


} // namespace end: codegen
