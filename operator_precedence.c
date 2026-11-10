
#include <stdio.h>
#include <string.h>

/*
ALGORITHM:

1. Read the arithmetic expression.
2. Append $ to the end of the input.
3. Initialize the stack with $.
4. Repeat until the expression is accepted or an error occurs:
   a. Find the topmost terminal in the stack.
   b. Compare it with the current input symbol.
   c. If both are $, ACCEPT.
   d. If both are operands, ERROR.
   e. If input has higher precedence, SHIFT.
   f. If stack contains an operand, REDUCE it to E.
   g. If stack contains E operator E, REDUCE it to E.
   h. Otherwise, ERROR.
5. Display stack, input and action at every step.


PSEUDOCODE:

Initialize stack = $
Read expression
Append $ to expression

While true:

    Find top terminal in stack
    a = top terminal
    b = current input

    If a == $ AND b == $:
        ACCEPT
        Stop

    If a == i AND b == i:
        ERROR
        Stop

    If input has higher precedence:
        SHIFT input to stack
        Move input pointer forward

    Else if stack top == i:
        Replace i with E
        REDUCE

    Else if stack contains E operator E:
        Replace E operator E with E
        REDUCE

    Else:
        ERROR
        Stop


LOGIC:

- Stack stores symbols being processed.
- Input stores the remaining expression.
- $ represents the beginning/end marker.
- i represents an operand.
- E represents a reduced expression.
- * and / have precedence 2.
- + and - have precedence 1.
- SHIFT moves an input symbol to the stack.
- REDUCE replaces an operand or E operator E with E.
- ACCEPT means the expression is valid.
- ERROR means the expression is invalid.
*/

char stack[100] = "$", input[100];
int top = 0, ip = 0;

// Find operator precedence
int level(char c)
{
    return (c == '*' || c == '/') ? 2 : 1;
}

int main()
{
    char a, b;

    printf("Enter the expression (use i for operand): ");
    scanf("%s", input);

    strcat(input, "$");

    printf("\n%-15s %-15s %s\n", "STACK", "INPUT", "ACTION");

    while (1)
    {
        int k = top;

        // Find topmost terminal, skipping E
        while (stack[k] == 'E')
            k--;

        a = stack[k];
        b = input[ip];

        printf("%-15s %-15s ", stack, input + ip);

        // Accept
        if (a == '$' && b == '$')
        {
            puts("ACCEPT");
            break;
        }

        // Invalid consecutive operands
        if (a == 'i' && b == 'i')
        {
            puts("ERROR");
            break;
        }

        // Check whether to shift
        int shift = a == '$' ||
                    (b != '$' && a != 'i' &&
                    (b == 'i' || level(a) < level(b)));

        if (shift)
        {
            stack[++top] = b;
            stack[top + 1] = '\0';
            ip++;

            puts("SHIFT");
        }

        // Reduce operand i to E
        else if (stack[top] == 'i')
        {
            stack[top] = 'E';
            puts("REDUCE");
        }

        // Reduce E operator E to E
        else if (top >= 2 &&
                 stack[top] == 'E' &&
                 stack[top - 2] == 'E' &&
                 strchr("+-*/", stack[top - 1]))
        {
            top -= 2;
            stack[top] = 'E';
            stack[top + 1] = '\0';

            puts("REDUCE");
        }

        else
        {
            puts("ERROR");
            break;
        }
    }

    return 0;
}
