#include "type.hpp"
#include <iostream>

using namespace std;

namespace codegen {

Type::Type(std::string name, bool isConst)
	: m_name(name), m_isConst(isConst)
{
}

std::string Type::getName() const
{
	return m_name;
}

bool Type::isConst() const
{
	return m_isConst;
}

void Type::setName(std::string name)
{
	m_name = name;
}

void Type::setConst(bool c)
{
	m_isConst = c;
}

std::ostream& operator<<(std::ostream &out, const Type &type)
{
	if (type.m_isConst)
		out << "const ";
	return out << type.m_name;
}

} // namespace end: codegen
