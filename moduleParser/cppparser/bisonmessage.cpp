#include "bisonmessage.hpp"

namespace parser {

BisonMessage::BisonMessage()
{

}

void BisonMessage::setMessage(parser::parserMessage msg)
{
	m_msg = msg;
}

void BisonMessage::setAllFine()
{
	m_msg = ALL_FINE;
}

void BisonMessage::setUnexpectedCrash()
{
	m_msg = UNEXPECTED_CRASH;
}

void BisonMessage::setSyntaxError()
{
	m_msg = SYNTAX_ERROR;
}

parserMessage BisonMessage::getStatus() const
{
	return m_msg;
}

bool BisonMessage::isAllFine() const
{
	return m_msg == ALL_FINE;
}

bool BisonMessage::isSyntaxError() const
{
	return m_msg == SYNTAX_ERROR;
}

bool BisonMessage::isUnexpectedCrash() const
{
	return m_msg == UNEXPECTED_CRASH;
}


} // namespace end: parser
