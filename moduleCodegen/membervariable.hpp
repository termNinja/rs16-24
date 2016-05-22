#ifndef MEMBERVARIABLE_HPP
#define MEMBERVARIABLE_HPP

#include "type.hpp"
#include "variable.hpp"

namespace codegen {

class MemberVariable : public Variable
{
public:
	// TODO: Switch QString owner to a const reference to real class
	MemberVariable(Type type, QString name, QString owner);

	QString getOwnerName() const;

	friend std::ostream& operator<<(std::ostream& out, const MemberVariable &mv);
private:
	QString m_owner;
};

} // namespace end: codegen

#endif // MEMBERVARIABLE_HPP
