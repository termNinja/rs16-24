#include "membervariable.hpp"
#include <iostream>

using namespace std;


namespace codegen {

MemberVariable::MemberVariable(Type type, QString name, QString owner)
	: Variable(type, name), m_owner(owner)
{
}

QString MemberVariable::getOwnerName() const
{
	return m_owner;
}

std::ostream &operator<<(std::ostream &out, const MemberVariable &mv)
{
	return out << mv.m_type <<  " "  << mv.m_owner.toStdString() << "::" << mv.m_name.toStdString();
}

} // namespace end: codegen
