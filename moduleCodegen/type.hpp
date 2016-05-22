#ifndef TYPE_HPP
#define TYPE_HPP

#include <QString>
#include <string>

namespace codegen {

class Type {
public:
	Type(std::string name, bool isConst = false);

	std::string getName() const;
	bool isConst() const;

	void setName(std::string name);
	void setConst(bool c);

	friend std::ostream& operator<<(std::ostream &out, const Type &type);

private:
	std::string m_name;
	bool m_isConst;
};

}
#endif // TYPE_HPP
