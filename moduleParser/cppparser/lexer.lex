%option noyywrap
%option nounput
%option noinput

%{
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "moduleCodegen/class.hpp"
#include "parser.bison.hpp"
%}

DIGIT [0-9]
%%
class 		{ return CLASS_t; 		}
public 		{ return PUBLIC_t; 		}
private 	{ return PRIVATE_t; 	}
protected 	{ return PROTECTED_t; 	}
const 		{ return CONST_t; 		}
static 		{ return STATIC_t; 		}

[a-zA-Z_][a-zA-Z0-9_]* {
	yylval.id = new std::string(yytext);
	return ID_t;
}

[+-]?{DIGIT}+ {
	yylval.intVal = atoi(yytext);
	return INTEGER_t;
}

[+-]?{DIGIT}+([.]{DIGIT}+)? {
	yylval.doubleVal = atof(yytext);
	return DOUBLE_t;
}

[/]{2}.* {}

[;:,{}()\[\]&+*/%-] {
	return *yytext;
}

[ \n\t] {}
. {
	std::cerr << "Unrecognized token. Found " << yytext << std::endl;
	std::cerr << "Lexer terminating program. " << std::endl;
	exit(1);
}
%%
