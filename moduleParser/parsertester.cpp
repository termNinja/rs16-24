#include <string>
#include <iostream>
#include <memory>
#include "parsertester.hpp"
#include "cppparser/cppparser.hpp"
#include "cppparser/bisonmessage.hpp"
#include "moduleCodegen/class.hpp"
#include "moduleLangExporter/cpplangexporter.hpp"

namespace parser {

ParserTester::ParserTester()
{

}

void ParserTester::performTest()
{
	CppParser cppParser;
	std::string parsingPath = "../rs16-24/parsingTests/cpp/10_full.hpp";
	std::unique_ptr<std::vector<codegen::Class* > > result = cppParser.parseClassFile(parsingPath);

	lexp::CppLangExporter cppExp;
	std::cout << "Parsing results (file: " << parsingPath << ")";

	for (auto cls : *result)
		std::cout << cppExp.genClass(*cls) << std::endl;


	for (auto cls : *result)
		delete cls;

}

} // namespace end: parser
