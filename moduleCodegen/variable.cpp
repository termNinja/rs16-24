#include "variable.hpp"
#include <iostream>

using namespace std;

namespace codegen {

Variable::Variable(Type type, std::string name)
	: m_type(type), m_name(name)
{
}

const Type &Variable::getType() const
{
	return m_type;
}

std::string Variable::getName() const
{
	return m_name;
}

void Variable::setType(const Type &type)
{
	m_type = type;
}

void Variable::setName(std::string name)
{
	m_name = name;
}

std::ostream& operator<<(std::ostream &out, const Variable &var)
{
	return out << var.m_type <<  " " << var.m_name;
}

} // namespace end: codegen
