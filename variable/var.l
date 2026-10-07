%{
#include "variable.tab.h"
%}

%%

[a-zA-Z][a-zA-Z0-9]*    return VARIABLE;
[ \t]                   ;
\n                      return '\n';
.                       return yytext[0];

%%

int yywrap()
{
    return 1;
}