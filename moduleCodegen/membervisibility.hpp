#ifndef MEMBERVISIBILITY_HPP
#define MEMBERVISIBILITY_HPP

#include <string>
#include <iostream>

namespace codegen {

typedef enum {
	PUBLIC, PRIVATE, PROTECTED
} MemberVisibility;

inline std::string getVisibilityAsString(MemberVisibility v)
{
	if (v == PUBLIC) return "public";
	else if (v == PRIVATE) return "private";
	else if (v == PROTECTED) return "protected";
	else {
		std::cerr << "Unknown visibility type." << std::endl;
		return "";
	}
}

} // namespace end: codegen

#endif // MEMBERVISIBILITY_HPP
