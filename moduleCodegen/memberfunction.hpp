#ifndef MEMBERFUNCTION_HPP
#define MEMBERFUNCTION_HPP

#include <string>
#include "type.hpp"
#include "variable.hpp"
#include "function.hpp"

namespace codegen {

class MemberFunction : public Function {
public:
	MemberFunction(std::string functionName, bool isConst = false);
	MemberFunction(Type returnType, std::string functionName, const std::vector<Variable> &parameters,
				   std::string owner, bool isConst = false);

	// TODO: Switch this to a reference to the owner class (later once I construct class)
	std::string getOwnerName() const;
	void setOwner(std::string className);
	bool isConst() const;

	friend std::ostream& operator<<(std::ostream& out, const MemberFunction &f);

private:
	std::string m_owner;
	bool m_isConst;
};

} // namespace end: codegen

#endif // MEMBERFUNCTION_HPP
