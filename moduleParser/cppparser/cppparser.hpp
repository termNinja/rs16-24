#ifndef CPPPARSER_HPP
#define CPPPARSER_HPP

#include <memory>
#include <vector>
#include <string>
#include "parser.hpp"
#include "moduleCodegen/class.hpp"

namespace parser {

class CppParser : public Parser {
public:
	unique_ptr<vector<codegen::Class *> > parseClassFile(string path) const;
};

} // namespace end: parser

#endif // CPPPARSER_HPP
