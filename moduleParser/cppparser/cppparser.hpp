#ifndef CPPPARSER_HPP
#define CPPPARSER_HPP

#include <memory>
#include <vector>
#include <string>
#include "parser.hpp"
#include "moduleCodegen/class.hpp"

namespace parser {

/**
 * @brief The CppParser class that parser c++ header files. Uses flex for lexical analysis and bison for syntax analysis.
 */
class CppParser : public Parser {
public:
	/**
	 * @brief Parses c++ header file given by PATH and returns codegen representation of given header.
	 * @param path Path to given c++ header file.
	 * @return unique_ptr to vector of Class* that contains classes that were found in the given header file.
	 */
	vector<codegen::Class *>*  parseClassFile(string path) const;
};

} // namespace end: parser

#endif // CPPPARSER_HPP
