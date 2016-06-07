#ifndef MEMBERVARIABLE_HPP
#define MEMBERVARIABLE_HPP

#include <string>
#include "type.hpp"
#include "variable.hpp"
#include "membervisibility.hpp"
#include "member.hpp"

namespace codegen {

class MemberVariable : public Variable, public Member {
public:
	// TODO: Switch QString owner to a const reference to real class
	MemberVariable(Type type, std::string name, std::string owner = "", MemberVisibility visibility = PRIVATE, bool isStatic = false);
    MemberVariable();

	std::string getOwnerName() const;
	bool isStatic() const;

	MemberVisibility getVisibility() const;
	void setVisibility(MemberVisibility visibility);
	void setStatic(bool isStatic);


	memberType getMemberType() const;

	friend std::ostream& operator<<(std::ostream& out, const MemberVariable &mv);
private:
	std::string m_owner;
	MemberVisibility m_visibility;
	bool m_isStatic;
};

} // namespace end: codegen

#endif // MEMBERVARIABLE_HPP
