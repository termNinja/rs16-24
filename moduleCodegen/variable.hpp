#ifndef VARIABLE_HPP
#define VARIABLE_HPP

#include <QString>
#include <string>
#include "type.hpp"

namespace codegen {

class Variable {
public:
	Variable(Type type, std::string name, bool isStatic = false);
    Variable();

	const Type& getType() const;
	std::string getName() const;
	bool isStatic() const;

	void setType(const Type &type);
	void setName(std::string name);
	void setStatic(bool isStatic);

	friend std::ostream& operator<<(std::ostream& out, const Variable &var);

protected:
	Type m_type;
	std::string m_name;
	bool m_isStatic;
};

} // namespace end: codegen

#endif // VARIABLE_HPP
