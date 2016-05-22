#include "membervariable.hpp"

namespace codegen {

MemberVariable::MemberVariable(Type type, std::string name, std::string owner)
	: Variable(type, name), m_owner(owner)
{
}

std::string MemberVariable::getOwnerName() const
{
	return m_owner;
}

std::ostream &operator<<(std::ostream &out, const MemberVariable &mv)
{
	return out << mv.m_type <<  " "  << mv.m_owner << "::" << mv.m_name;
}

} // namespace end: codegen
