#include "type.hpp"

Type::Type(QString name, bool isConst)
	: m_name(name), m_isConst(isConst)
{
}

QString Type::getName() const
{
	return m_name;
}

bool Type::isConst() const
{
	return m_isConst;
}

void Type::setName(QString name)
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
	return out << type.m_name.toStdString();
}
