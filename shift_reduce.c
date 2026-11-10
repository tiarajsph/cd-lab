
/*
ALGORITHM:
1. Read the input expression.
2. Add '$' to the end of the input.
3. Initialize the stack with '$'.
4. Repeat until the input reaches '$':
   a. Shift the next input symbol onto the stack.
   b. Check whether a handle exists on top of the stack.
   c. If a handle exists, reduce it to E.
   d. Repeat reduction until no more handles exist.
5. Perform any remaining reductions.
6. If the stack contains '$E', accept; otherwise reject.

PSEUDOCODE:
START
    Read expression
    Append '$' to expression
    Push '$' onto stack

    WHILE input is not '$'
        Push next input symbol onto stack
        Print SHIFT

        WHILE reduction is possible
            Replace handle with E
            Print REDUCE

    WHILE reduction is possible
        Replace handle with E
        Print REDUCE

    IF stack contains '$E'
        Print ACCEPT
    ELSE
        Print REJECT
END

LOGIC:
- i represents an identifier.
- E represents an expression.
- Shift moves an input symbol to the stack.
- Reduce replaces a handle with E.
- Handles: i, E+E, E-E, E*E, E/E and (E).
- '$' marks the beginning of the stack and end of input.
*/

#include <stdio.h>
#include <string.h>

char s[100], in[100];       // Stack and input
int top = -1, ip = 0;       // Stack top and input position

// Function to reduce handles into E
int reduce()
{
    // i -> E
    if (s[top] == 'i') {
        s[top] = 'E';
        return 1;
    }

    // E+E, E-E, E*E or E/E -> E
    if (top >= 2 && s[top-2] == 'E' &&
        (s[top-1] == '+' || s[top-1] == '-' ||
         s[top-1] == '*' || s[top-1] == '/') &&
        s[top] == 'E') {

        top -= 2;
        s[top] = 'E';
        s[top+1] = '\0';
        return 1;
    }

    // (E) -> E
    if (top >= 2 && s[top-2] == '(' &&
        s[top-1] == 'E' && s[top] == ')') {

        top -= 2;
        s[top] = 'E';
        s[top+1] = '\0';
        return 1;
    }

    return 0;               // No handle found
}

int main()
{
    printf("Enter expression (use i for identifier): ");
    scanf("%99s", in);

    strcat(in, "$");        // Append end marker

    s[++top] = '$';         // Initialize stack

    printf("\nStack\tInput\tAction\n");

    while (in[ip] != '$') {

        s[++top] = in[ip++];    // Shift input symbol
        s[top+1] = '\0';

        printf("%s\t%s\tShift\n", s, in+ip);

        while (reduce())        // Reduce while possible
            printf("%s\t%s\tReduce\n", s, in+ip);
    }

    while (reduce())            // Final reductions
        printf("%s\t%s\tReduce\n", s, in+ip);

    if (top == 1 && s[0] == '$' && s[1] == 'E')
        printf("\nExpression Accepted\n");
    else
        printf("\nExpression Rejected\n");

    return 0;
}
