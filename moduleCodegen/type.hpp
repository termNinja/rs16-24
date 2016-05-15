#ifndef TYPE_HPP
#define TYPE_HPP

#include <QString>

class Type {
public:
	Type(QString name, bool isConst = false);

	QString getName() const;
	bool isConst() const;

	void setName(QString name);
	void setConst(bool c);

private:
	QString m_name;
	bool m_isConst;
};

#endif // TYPE_HPP
