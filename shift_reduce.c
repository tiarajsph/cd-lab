
#include <stdio.h>
#include <string.h>

char s[100], in[100];
int top = -1, ip = 0;

int reduce()
{
    if (s[top] == 'i') {
        s[top] = 'E';
        return 1;
    }

    if (top >= 2 &&
        ((s[top-2] == 'E' &&
          (s[top-1] == '+' || s[top-1] == '*') &&
          s[top] == 'E') ||
         (s[top-2] == '(' &&
          s[top-1] == 'E' && s[top] == ')'))) {
        top -= 2;
        s[top] = 'E';
        s[top+1] = '\0';
        return 1;
    }

    return 0;
}

int main()
{
    printf("Enter expression (use i for identifier): ");
    scanf("%99s", in);
    strcat(in, "$");

    s[++top] = '$';
    printf("\nStack\tInput\tAction\n");

    while (in[ip] != '$') {
        s[++top] = in[ip++];
        s[top+1] = '\0';
        printf("%s\t%s\tShift\n", s, in+ip);

        while (reduce())
            printf("%s\t%s\tReduce\n", s, in+ip);
    }

    while (reduce())
        printf("%s\t%s\tReduce\n", s, in+ip);

    if (top == 1 && s[0] == '$' && s[1] == 'E')
        printf("\nExpression Accepted\n");
    else
        printf("\nExpression Rejected\n");

    return 0;
}
