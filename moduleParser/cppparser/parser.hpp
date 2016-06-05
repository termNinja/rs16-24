#ifndef PARSER_HPP
#define PARSER_HPP

#include <memory>
#include <vector>
#include <string>
#include "moduleCodegen/class.hpp"

using std::unique_ptr;
using std::vector;
using std::string;

namespace parser {

class Parser {
public:
	// This method returns an unique pointer to a vector of classes
	// that were parsed from a file given by path parameter.
	virtual unique_ptr<vector<codegen::Class *> > parseClassFile(string path) const = 0;
	virtual ~Parser() {}
private:
};

} // namespace end: parser

#endif // PARSER_HPP
