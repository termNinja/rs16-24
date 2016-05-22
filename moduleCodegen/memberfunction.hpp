#ifndef MEMBERFUNCTION_HPP
#define MEMBERFUNCTION_HPP

#include <string>
#include "type.hpp"
#include "variable.hpp"
#include "function.hpp"

namespace codegen {

class MemberFunction : public Function {
public:
	MemberFunction(Type returnType, std::string functionName, const std::vector<Variable> &parameters,
				   std::string owner, bool isConst = false);

	// TODO: Switch this to a reference to the owner class (later once I construct class)
	std::string getOwnerName() const;
	bool isConst() const;

	friend std::ostream& operator<<(std::ostream& out, const MemberFunction &f);
private:
	std::string m_owner;
	bool m_isConst;
};

}

#endif // MEMBERFUNCTION_HPP
