%{
#include <stdio.h>


int yylex();
void yyerror(const char *s);
%}

%token VARIABLE

%%

input:
    | input line
    ;

line:
      '\n'
    | VARIABLE '\n'
      {
          printf("Result: Valid Variable\n");
      }
    ;

%%

void yyerror(const char *s)
{
    printf("Result: Invalid Variable\n");
}

int main()
{
    printf("Enter a variable name: ");
    yyparse();
    return 0;
}