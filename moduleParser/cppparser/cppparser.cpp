#include <iostream>
#include <cstdio>
#include "cppparser.hpp"
#include "bisonmessage.hpp"

extern int yyparse();
extern FILE* yyin;
extern vector<codegen::Class *> *parsingResult;

parser::BisonMessage bisonMessage;
namespace parser {

using std::vector;
using std::string;
using std::unique_ptr;


vector<codegen::Class *>* CppParser::parseClassFile(string path) const
{
	// TODO: First we check does the file exist at all?
	// ...

	// We set up input file for bison to read and parse
	if ((yyin = fopen(path.c_str(), "r")) == NULL) {
		std::cerr << "Failed opening file at: " << path << std::endl;	
		return nullptr;
	}

	// We declare an variable that bison shall use to report errors
//	bisonMessage = UNEXPECTED_CRASH;

	// Bison shall return the result of parsing inside this variable
	// extern unique_ptr< vector<codegen::Class *> > parsingResult;

	// We call bison to parse the file
	yyparse();

	// We check the parsing status
	if (bisonMessage.isSyntaxError()) {
		std::cerr << "Parser has discovered a syntax error during parsing of file: " << path << std::endl;
	} else if (bisonMessage.isUnexpectedCrash()) {
		std::cerr << "Bison backend parser has crashed. :(" << std::endl;	
	} else if (bisonMessage.isAllFine()) {
		// And finally, we return the result
		// -> By returning unique_ptr we wish to say that
		// 		the user is responisble for cleaning up dynamically allocated objects
		// -> Quite often, vector shall contain only 1 class per file which is
		// 		usually the practice, but some c++ files contain multiples classes => We use vector.
//		return unique_ptr<vector<codegen::Class *> >(parsingResult);
		return parsingResult;
	}

	return nullptr;
}

} // namespace end: parser
