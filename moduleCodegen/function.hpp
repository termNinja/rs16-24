#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <vector>
#include <string>
#include "type.hpp"
#include "variable.hpp"

namespace codegen {

class Function {
public:
	Function(Type returnType, std::string functionName, const std::vector<Variable> &parameters);

	Type getReturnType() const;
	std::string getName() const;
	const std::vector<Variable>& getParameters() const;
	unsigned int getNumberOfParameters() const;

	void setReturnType(Type returnType);
	void setName(std::string name);
	void setParameters(const std::vector<Variable> &parameters);

	friend std::ostream& operator<<(std::ostream &out, const Function &function);

protected:
	Type m_returnType;
	std::string m_name;
	std::vector<Variable> m_parameters;
};

}
#endif // FUNCTION_HPP
