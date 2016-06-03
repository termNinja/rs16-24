#ifndef MEMBERVARIABLE_HPP
#define MEMBERVARIABLE_HPP

#include <string>
#include "type.hpp"
#include "variable.hpp"
#include "membervisibility.hpp"

namespace codegen {

class MemberVariable : public Variable
{
public:
	// TODO: Switch QString owner to a const reference to real class
	MemberVariable(Type type, std::string name, std::string owner, MemberVisibility visibility = PRIVATE);

	std::string getOwnerName() const;

	MemberVisibility getVisibility() const;
	void setVisibility(MemberVisibility visibility);

	friend std::ostream& operator<<(std::ostream& out, const MemberVariable &mv);
private:
	std::string m_owner;
	MemberVisibility m_visibility;
};

} // namespace end: codegen

#endif // MEMBERVARIABLE_HPP
