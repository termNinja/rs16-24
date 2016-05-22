#ifndef MEMBERFUNCTION_HPP
#define MEMBERFUNCTION_HPP

#include <QString>
#include "type.hpp"
#include "variable.hpp"
#include "function.hpp"

namespace codegen {

class MemberFunction : public Function {
public:
	MemberFunction(Type returnType, QString functionName, const std::vector<Variable> &parameters, QString owner);

	// TODO: Switch this to a reference to the owner class (later once I construct class)
	QString getOwnerName() const;

	friend std::ostream& operator<<(std::ostream& out, const MemberFunction &f);
private:
	QString m_owner;
};

}

#endif // MEMBERFUNCTION_HPP
