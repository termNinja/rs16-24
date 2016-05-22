#include "memberfunction.hpp"

namespace codegen {

MemberFunction::MemberFunction(codegen::Type returnType, std::string functionName,
							   const std::vector<codegen::Variable> &parameters, std::string owner, bool isConst)
	: Function(returnType, functionName, parameters), m_owner(owner)
{

}

std::string MemberFunction::getOwnerName() const
{
	return m_owner;
}

bool MemberFunction::isConst() const
{
	return m_isConst;
}

std::ostream &operator<<(std::ostream &out, const MemberFunction &function)
{
	out << function.m_returnType << " " << function.m_owner
		<< "::" << function.m_name << "(";
	for (unsigned i = 0; i < function.m_parameters.size()-1; ++i)
		out << function.m_parameters[i] << ", ";
	out << function.m_parameters.back() << ")";
	return out;
}

} // namespace end: codegen
