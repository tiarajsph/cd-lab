
/*
ALGORITHM:
1. Read the input character by character.
2. Identify the keyword "for".
3. Identify identifiers and numbers.
4. Identify relational and increment/decrement operators.
5. Ignore spaces and newlines.
6. Return all recognized tokens to YACC.
7. Return other symbols as they are.

PSEUDOCODE:
START
    Read input
    IF "for", return FOR
    ELSE IF identifier, return ID
    ELSE IF number, return NUM
    ELSE IF relational operator, return its token
    ELSE IF ++ or --, return its token
    ELSE IF whitespace, ignore
    ELSE return character
END

CORE LOGIC:
- yytext stores the matched text.
- return sends a token to YACC.
- ID represents an identifier.
- NUM represents a number.
- FOR represents the for keyword.
- LE, GE, EQ, NE represent relational operators.
- INC and DEC represent ++ and --.
*/

%{
#include "y.tab.h"
%}

%%

"for"                       return FOR;
[a-zA-Z_][a-zA-Z0-9_]*      return ID;
[0-9]+                      return NUM;

"<="                        return LE;
">="                        return GE;
"=="                        return EQ;
"!="                        return NE;
"++"                        return INC;
"--"                        return DEC;

[ \t\n]                     ;
.                           return yytext[0];

%%

// End of input
int yywrap()
{
    return 1;
}
