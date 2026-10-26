#include <stdio.h>
#include <string.h>
#include <ctype.h>

char stack[50], opnd[50][10];
int top = -1, n = -1, temp = 1;

int prec(char c)
{
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}

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
    int i;

    printf("Enter expression: ");
    scanf("%99s", s);

    printf("\nThree Address Code:\n");

    for (i = 0; s[i] != '\0'; i++)
    {
        char c = s[i];

        if (isalnum(c))
        {
            opnd[++n][0] = c;
            opnd[n][1] = '\0';
        }
        else if (c == '(')
            stack[++top] = c;

        else if (c == ')')
        {
            while (top != -1 && stack[top] != '(')
                reduce();

            top--;  // Remove '('
        }
        else
        {
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