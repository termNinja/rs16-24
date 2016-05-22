#include "memberfunction.hpp"
#include <iostream>

using namespace std;


namespace codegen {

MemberFunction::MemberFunction(codegen::Type returnType, QString functionName,
							   const std::vector<codegen::Variable> &parameters, QString owner)
	: Function(returnType, functionName, parameters), m_owner(owner)
{

}

QString MemberFunction::getOwnerName() const
{
	return m_owner;
}

std::ostream &operator<<(std::ostream &out, const MemberFunction &function)
{
	out << function.m_returnType << " " << function.m_owner.toStdString()
		<< "::" << function.m_name.toStdString() << "(";
	for (unsigned i = 0; i < function.m_parameters.size()-1; ++i)
		out << function.m_parameters[i] << ", ";
	out << function.m_parameters.back() << ")";
	return out;
}

} // namespace end: codegen
