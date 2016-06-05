#ifndef BISONMESSAGE_HPP
#define BISONMESSAGE_HPP

namespace parser {

typedef enum {
	SYNTAX_ERROR, ALL_FINE, UNEXPECTED_CRASH,
} parserMessage;

class BisonMessage {
public:
	BisonMessage();

	void setMessage(parserMessage msg);
	void setAllFine();
	void setUnexpectedCrash();
	void setSyntaxError();

	parserMessage getStatus() const;
	bool isAllFine() const;
	bool isSyntaxError() const;
	bool isUnexpectedCrash() const;

private:
	parserMessage m_msg;
};

} // namespace end

#endif // BISONMESSAGE_HPP
