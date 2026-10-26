
#include <stdio.h>
#include <string.h>

/* Stack stores symbols during parsing */
char stack[100];
int top = 0;              /* Index of top of stack */

/* input stores expression; ip points to current input symbol */
char input[100];
int ip = 0;

/* Terminal order used in the precedence table:
   +, *, (, ), i, $ */
char terminals[] = "+*()i$";

/* Precedence table:
   < means SHIFT
   = means SHIFT (matching parentheses or end marker)
   > means REDUCE
   blank means INVALID */
char table[6][6] = {
    {'>', '<', '<', '>', '<', '>'}, /* + */
    {'>', '>', '<', '>', '<', '>'}, /* * */
    {'<', '<', '<', '=', '<', ' '}, /* ( */
    {'>', '>', ' ', '>', ' ', '>'}, /* ) */
    {'>', '>', ' ', '>', ' ', '>'}, /* i */
    {'<', '<', '<', ' ', '<', '='}  /* $ */
};


/* Find the index of a terminal in the table.
   Example: indexOf('+') = 0, indexOf('i') = 4.
   Return -1 if the character is not a terminal. */
int indexOf(char c)
{
    int i;

    for (i = 0; i < 6; i++)
        if (terminals[i] == c)
            return i;

    return -1;
}


/* Find the topmost TERMINAL in the stack.
   Ignore E because E is a non-terminal.
   The precedence table compares terminals only. */
char topTerminal()
{
    int i;

    for (i = top; i >= 0; i--)
    {
        if (indexOf(stack[i]) != -1)
            return stack[i];
    }

    return '$';
}


/* REDUCE: Replace a recognized RHS with E.
   Return 1 if reduction succeeds, otherwise return 0. */
int reduce()
{
    /* E + E -> E */
    if (top >= 2 &&
        stack[top-2] == 'E' &&
        stack[top-1] == '+' &&
        stack[top] == 'E')
    {
        top = top - 2;
        stack[top] = 'E';
        stack[top+1] = '\0';
        return 1;
    }

    /* E * E -> E */
    if (top >= 2 &&
        stack[top-2] == 'E' &&
        stack[top-1] == '*' &&
        stack[top] == 'E')
    {
        top = top - 2;
        stack[top] = 'E';
        stack[top+1] = '\0';
        return 1;
    }

    /* ( E ) -> E */
    if (top >= 2 &&
        stack[top-2] == '(' &&
        stack[top-1] == 'E' &&
        stack[top] == ')')
    {
        top = top - 2;
        stack[top] = 'E';
        stack[top+1] = '\0';
        return 1;
    }

    /* i -> E */
    if (stack[top] == 'i')
    {
        stack[top] = 'E';
        return 1;
    }

    /* No pattern matched */
    return 0;
}


int main()
{
    char a, b, relation;
    int row, col;

    printf("Enter expression (use i for identifier): ");
    scanf("%99s", input);

    /* Append $ to mark the end of input */
    strcat(input, "$");

    /* Initialize stack with $ */
    stack[0] = '$';
    stack[1] = '\0';

    printf("\nStack\tInput\tAction\n");

    while (1)
    {
        /* ACCEPT:
           Stack contains $E and input is exhausted ($). */
        if (top == 1 &&
            stack[0] == '$' &&
            stack[1] == 'E' &&
            input[ip] == '$')
        {
            printf("%s\t%s\tAccept\n", stack, input + ip);
            break;
        }

        /* a = topmost terminal in stack
           b = current input symbol */
        a = topTerminal();
        b = input[ip];

        /* Convert both terminals to table indices */
        row = indexOf(a);
        col = indexOf(b);

        /* Invalid character: never index the table with -1 */
        if (row == -1 || col == -1)
        {
            printf("Invalid expression\n");
            break;
        }

        /* Get precedence relation between a and b */
        relation = table[row][col];

        /* SHIFT when relation is < or = */
        if (relation == '<' || relation == '=')
        {
            stack[++top] = b;
            stack[top+1] = '\0';

            printf("%s\t%s\tShift %c\n",
                   stack, input + ip, b);

            ip++;  /* Consume the input symbol */
        }

        /* REDUCE when relation is > */
        else if (relation == '>')
        {
            if (reduce())
            {
                printf("%s\t%s\tReduce\n",
                       stack, input + ip);
            }
            else
            {
                printf("Invalid expression\n");
                break;
            }
        }

        /* Blank table entry means invalid expression */
        else
        {
            printf("Invalid expression\n");
            break;
        }
    }

    return 0;
}
