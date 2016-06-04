#ifndef MEMBERCONSTRUCTOR_HPP
#define MEMBERCONSTRUCTOR_HPP

#include <string>
#include "function.hpp"
#include "member.hpp"
#include "membervisibility.hpp"

namespace codegen {

class MemberConstructor : public Function, public Member {
public:
	MemberConstructor(MemberVisibility visibility = MemberVisibility::PUBLIC);
	MemberConstructor(std::string owner = "", MemberVisibility visibility = MemberVisibility::PUBLIC);

	std::string getClassName() const;
	void setOwner(std::string owner);
	MemberVisibility getVisibility() const;
	void setVisibility(MemberVisibility visibility);

	memberType getMemberType() const;
private:
	std::string m_owner;
	MemberVisibility m_visibility;

	// This method is from Function parent class.
	// We hide it because constructor doesn't have a return type.
	Type getReturnType() const;
};

} // namespace end: codegen

#endif // MEMBERCONSTRUCTOR_HPP
