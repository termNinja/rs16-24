#ifndef VARIABLE_HPP
#define VARIABLE_HPP

#include <QString>
#include "type.hpp"

namespace codegen {

class Variable {
public:
	Variable(Type type, QString name);

	const Type& getType() const;
	QString getName() const;

	void setType(const Type &type);
	void setName(QString name);

	friend std::ostream& operator<<(std::ostream& out, const Variable &var);

protected:
	Type m_type;
	QString m_name;
};

}
#endif // VARIABLE_HPP
