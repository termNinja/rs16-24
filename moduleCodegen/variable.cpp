#include "variable.hpp"
#include <iostream>

using namespace std;

namespace codegen {

Variable::Variable(Type type, QString name)
	: m_type(type), m_name(name)
{
}

const Type &Variable::getType() const
{
	return m_type;
}

QString Variable::getName() const
{
	return m_name;
}

void Variable::setType(const Type &type)
{
	m_type = type;
}

void Variable::setName(QString name)
{
	m_name = name;
}

std::ostream& operator<<(std::ostream &out, const Variable &var)
{
	return out << var.m_type <<  " " << var.m_name.toStdString();
}

} // namespace end: codegen
