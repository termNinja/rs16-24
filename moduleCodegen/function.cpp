#include "function.hpp"

namespace codegen {

Function::Function(Type returnType, std::string functionName, const std::vector<Variable> &parameters)
	: m_returnType(returnType), m_name(functionName), m_parameters(parameters)
{
}

Type Function::getReturnType() const
{
	return m_returnType;
}

std::string Function::getName() const
{
	return m_name;
}

const std::vector<Variable> &Function::getParameters() const
{
	return m_parameters;
}

unsigned int Function::getNumberOfParameters() const
{
	return static_cast<unsigned>(m_parameters.size());
}

void Function::setReturnType(Type returnType)
{
	m_returnType = returnType;
}

void Function::setName(std::string name)
{
	m_name = name;
}

void Function::setParameters(const std::vector<Variable> &parameters)
{
	m_parameters = parameters;
}

std::ostream& operator<<(std::ostream &out, const Function &function)
{
	out << function.m_returnType << " " << function.m_name
		<< "(";
	for (unsigned i = 0; i < function.m_parameters.size()-1; ++i)
		out << function.m_parameters[i] << ", ";
	out << function.m_parameters.back() << ")";
	return out;
}

} // namespace end: codegen
