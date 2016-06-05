// Let's parser classes about parser with our own parser
// that maps parsed classes on our custom classes that represent classes! 
// Matrix.

class CppParser {
public:
	CppParser();
	CppParser(string &path);

	// Returns true if parsing was successful
	bool startParsing(string path);

	const string& getCurrentParsingPath() const;

	void setParsingPath(string s);

private:
	string m_path;
	const string m_indicator;
};

class ParserTester {
public:
	ParserTester(CppParser *parser);
	ParserTester(CppParser &parser);

	const CppParser& getParser() const;
	bool runParser() const;

private:
	CppParser *m_parser;
};
