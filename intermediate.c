/*
ALGORITHM:
1. Read the arithmetic expression.
2. Initialize an operator stack and an operand stack.
3. Scan the expression from left to right.
4. If the symbol is an operand, push it onto the operand stack.
5. If the symbol is '(' , push it onto the operator stack.
6. If the symbol is ')', reduce operators until '(' is found.
7. If the symbol is an operator:
   a. Compare its precedence with the top operator.
   b. Reduce operators with higher or equal precedence.
   c. Push the current operator.
8. Reduce all remaining operators.
9. Display the generated Three Address Code.

PSEUDOCODE:
START
    Read expression

    FOR each character in expression
        IF character is an operand
            Push it onto operand stack

        ELSE IF character is '('
            Push it onto operator stack

        ELSE IF character is ')'
            WHILE top operator is not '('
                REDUCE

            Pop '('

        ELSE
            WHILE top operator has higher or equal precedence
                REDUCE

            Push current operator

    WHILE operator stack is not empty
        REDUCE

END

CORE LOGIC:
- stack[] stores operators.
- opnd[][] stores operands and temporary variables.
- prec() determines operator precedence:
      * and / have precedence 2
      + and - have precedence 1.
- reduce() pops one operator and two operands.
- It generates a temporary variable (t1, t2, etc.).
- It prints the TAC instruction:
      temp = operand1 operator operand2
- The generated temporary variable is pushed back
  onto the operand stack.
- Parentheses ensure expressions inside them are
  evaluated first.
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char stack[50], opnd[50][10];
int top = -1, n = -1, temp = 1;

// Operator precedence
int prec(char c)
{
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}

// Reduce operator and two operands into one temporary
void reduce()
{
    char op = stack[top--];
    char b[10], a[10], t[10];

    strcpy(b, opnd[n--]);
    strcpy(a, opnd[n--]);

    sprintf(t, "t%d", temp++);
    printf("%s = %s %c %s\n", t, a, op, b);

    strcpy(opnd[++n], t);
}

int main()
{
    char s[100];
    printf("Enter expression: ");
    scanf("%99s", s);

    printf("\nThree Address Code:\n");

    for (int i = 0; s[i]; i++) {
        char c = s[i];

        if (isalnum(c)) {
            opnd[++n][0] = c;
            opnd[n][1] = '\0';
        }
        else if (c == '(')
            stack[++top] = c;

        else if (c == ')') {
            while (stack[top] != '(')
                reduce();
            top--;
        }
        else {
            while (top != -1 && stack[top] != '(' &&
                   prec(stack[top]) >= prec(c))
                reduce();

            stack[++top] = c;
        }
    }

    while (top != -1)
        reduce();

    return 0;
}
