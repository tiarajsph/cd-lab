
/*
ALGORITHM:
1. Read tokens from LEX.
2. Check whether the statement starts with FOR.
3. Check opening parenthesis.
4. Validate initialization.
5. Check first semicolon.
6. Validate condition.
7. Check second semicolon.
8. Validate increment/decrement.
9. Check closing parenthesis.
10. Validate the loop body.
11. Print whether the FOR statement is valid.

PSEUDOCODE:
START
    Read tokens

    Check FOR keyword
    Check '('

    Check initialization
    Check ';'

    Check condition
    Check ';'

    Check increment
    Check ')'

    Check body

    IF all rules match
        Print Valid
    ELSE
        Print Invalid
END

CORE LOGIC:
- FOR represents the for keyword.
- ID represents an identifier.
- NUM represents a number.
- initialization checks the starting value.
- condition checks the loop condition.
- increment checks ++, -- or assignment.
- relop checks relational operators.
- expr handles arithmetic expressions.
- body handles the loop body.
- yyparse() checks the grammar.
- yyerror() displays an error.
*/

%{
#include <stdio.h>

int yylex();
void yyerror(const char *s);
%}

// Declare tokens
%token FOR ID NUM LE GE EQ NE INC DEC

%%

// Main program
program:
    for_stmt
    {
        printf("\nResult: Valid FOR statement syntax\n");
    }
    ;

// Structure of FOR loop
for_stmt:
    FOR '(' initialization ';' condition ';' increment ')' body
    ;

// Initialization part
initialization:
      /* empty */
    | ID '=' expr
    ;

// Condition part
condition:
      /* empty */
    | expr relop expr
    | expr
    ;

// Increment or decrement part
increment:
      /* empty */
    | ID '=' expr
    | ID INC
    | ID DEC
    | INC ID
    | DEC ID
    ;

// Relational operators
relop:
      '<'
    | '>'
    | LE
    | GE
    | EQ
    | NE
    ;

// Arithmetic expressions
expr:
      ID
    | NUM
    | expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | '(' expr ')'
    ;

// Loop body
body:
      ';'
    | '{' statement_list '}'
    | statement
    ;

// Multiple statements inside body
statement_list:
      /* empty */
    | statement_list statement
    ;

// Individual statement
statement:
      ID '=' expr ';'
    | for_stmt
    ;

%%

// Display syntax error
void yyerror(const char *s)
{
    printf("\nResult: Invalid FOR statement syntax\n");
}

// Main function
int main()
{
    printf("Enter a C 'for' statement:\n");
    yyparse();

    return 0;
}
