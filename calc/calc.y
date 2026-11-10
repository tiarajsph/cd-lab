
/*
ALGORITHM:
1. Read tokens from LEX.
2. If a number is found, use its value.
3. If an operator is found, perform the corresponding operation.
4. Follow operator precedence:
   a. Multiplication and division first.
   b. Addition and subtraction next.
5. Evaluate parentheses first.
6. Handle unary minus.
7. Print the final result.
8. Display an error for division by zero.

PSEUDOCODE:
START
    Read expression

    IF NUMBER
        Return its value

    IF addition
        Add operands

    IF subtraction
        Subtract operands

    IF multiplication
        Multiply operands

    IF division
        Check divisor
        Divide operands

    IF parentheses
        Evaluate inside expression

    IF unary minus
        Negate value

    Print result
END

CORE LOGIC:
- yyparse() starts parsing.
- yylex() gets tokens from LEX.
- NUMBER represents an integer.
- $1 represents first operand.
- $2 represents second operand.
- $3 represents third operand.
- $$ stores the result of a grammar rule.
- %left defines left associativity.
- %right defines right associativity.
- UMINUS handles unary minus.
*/

%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);
%}

// Declare number token
%token NUMBER

// Operator precedence
%left '+' '-'
%left '*' '/'
%right UMINUS

%%

// Main grammar
calculation:
    | calculation line
    ;

// Each line contains an expression
line:
      '\n'
    | expr '\n'
      {
          printf("Result: %d\n", $1);
      }
    ;

// Expression rules
expr:
      NUMBER
      {
          $$ = $1;
      }

    | expr '+' expr
      {
          $$ = $1 + $3;
      }

    | expr '-' expr
      {
          $$ = $1 - $3;
      }

    | expr '*' expr
      {
          $$ = $1 * $3;
      }

    | expr '/' expr
      {
          if ($3 == 0)
          {
              yyerror("Division by zero");
              $$ = 0;
          }
          else
              $$ = $1 / $3;
      }

    | '(' expr ')'
      {
          $$ = $2;
      }

    | '-' expr %prec UMINUS
      {
          $$ = -$2;
      }
    ;

%%

// Display errors
void yyerror(const char *s)
{
    printf("Error: %s\n", s);
}

// Main function
int main()
{
    printf("Enter expressions:\n");
    yyparse();

    return 0;
}
