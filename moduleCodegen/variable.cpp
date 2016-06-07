#include "variable.hpp"
#include <iostream>

using namespace std;

namespace codegen {

Variable::Variable(Type type, std::string name, bool isStatic)
	: m_type(type), m_name(name), m_isStatic(isStatic)
{
}

Variable::Variable()
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

bool Variable::isStatic() const
{
	return m_isStatic;
}

void Variable::setType(const Type &type)
{
	m_type = type;
}

void Variable::setName(std::string name)
{
	m_name = name;
}

void Variable::setStatic(bool isStatic)
{
	m_isStatic = isStatic;
}

std::ostream& operator<<(std::ostream &out, const Variable &var)
{
	return out << var.m_type <<  " " << var.m_name;
}

} // namespace end: codegen
