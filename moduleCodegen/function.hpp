#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <vector>
#include <QString>
#include "type.hpp"
#include "variable.hpp"

namespace codegen {

class Function {
public:
	Function(Type returnType, QString functionName, const std::vector<Variable> &parameters);

	Type getReturnType() const;
	QString getName() const;
	const std::vector<Variable>& getParameters() const;
	unsigned long int getNumberOfParameters() const;

	void setReturnType(Type returnType);
	void setName(QString name);
	void setParameters(const std::vector<Variable> &parameters);

	friend std::ostream& operator<<(std::ostream &out, const Function &function);

protected:
	Type m_returnType;
	QString m_name;
	std::vector<Variable> m_parameters;
};

}
#endif // FUNCTION_HPP
