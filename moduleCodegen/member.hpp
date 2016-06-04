#ifndef MEMBER_HPP
#define MEMBER_HPP

namespace codegen {

typedef enum {
	MEMBER_VARIABLE, MEMBER_FUNCTION, MEMBER_CONSTRUCTOR
} memberType;

class Member {
public:
	virtual memberType getMemberType() const = 0;
	virtual ~Member() {}
};

} // namespace end: codegen

#endif // MEMBER_HPP
