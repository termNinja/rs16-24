#ifndef MEMBERFUNCTION_HPP
#define MEMBERFUNCTION_HPP

#include <string>
#include "type.hpp"
#include "variable.hpp"
#include "function.hpp"
#include "membervisibility.hpp"
#include "member.hpp"

namespace codegen {

class MemberFunction : public Function, public Member {
public:
	MemberFunction(Type returnType, std::string functionName, bool isConst = false, MemberVisibility visibililty = PRIVATE, bool isStatic = false);
	MemberFunction(Type returnType, std::string functionName, const std::vector<Variable> &parameters,
				   std::string owner, bool isConst = false, MemberVisibility visibility = PRIVATE, bool isStatic = false);

	// TODO: Switch this to a reference to the owner class (later once I construct class)
	std::string getOwnerName() const;
	bool isConst() const;
	bool isStatic() const;
	MemberVisibility getVisibility() const;

	void setVisibility(MemberVisibility visibility);
	void setOwner(std::string className);
	void setStatic(bool isStatic);

	memberType getMemberType() const;

	friend std::ostream& operator<<(std::ostream& out, const MemberFunction &f);

private:
	std::string m_owner;
	bool m_isConst;
	bool m_isStatic;
	MemberVisibility m_visibility;
};

} // namespace end: codegen

#endif // MEMBERFUNCTION_HPP
