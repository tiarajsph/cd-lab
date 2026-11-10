
/*
ALGORITHM:
1. Read the input character by character.
2. If digits are found, collect the number.
3. Convert the number into an integer.
4. Return NUMBER to YACC.
5. If an operator or parenthesis is found, return it.
6. Ignore spaces and tabs.
7. Return newline when a line ends.

PSEUDOCODE:
START
    Read characters
    IF digit
        Convert to integer
        Return NUMBER
    ELSE IF operator or parenthesis
        Return character
    ELSE IF newline
        Return newline
    ELSE IF space
        Ignore
END

CORE LOGIC:
- yylex() scans the input.
- yytext contains the matched text.
- atoi() converts text into an integer.
- yylval passes the number to YACC.
- NUMBER represents a numeric token.
*/

%{
#include "y.tab.h"
#include <stdlib.h>
%}

%%

[0-9]+      { yylval = atoi(yytext); return NUMBER; }
[ \t]       ;
\n          { return '\n'; }
[-+*/()]    { return yytext[0]; }
.           { /* Ignore unknown characters */ }

%%

// End of input
int yywrap()
{
    return 1;
}
