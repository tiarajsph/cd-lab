#include <stdio.h>

int main()
{
    int n, i;
    char dest[10], a[10], b[10], op;

    printf("Enter number of three address instructions: ");
    scanf("%d", &n);

    printf("Enter the three address code:\n");
    printf("Generated 8086 Assembly Code:\n\n");

    for (i = 0; i < n; i++)
    {
        scanf("%9s = %9s %c %9s", dest, a, &op, b);

        printf("MOV AX, %s\n", a);

        if (op == '+')
            printf("ADD AX, %s\n", b);

        else if (op == '-')
            printf("SUB AX, %s\n", b);

        else if (op == '*')
        {
            printf("MOV BX, %s\n", b);
            printf("MUL BX\n");
        }
        else if (op == '/')
        {
            printf("MOV BX, %s\n", b);
            printf("XOR DX, DX\n");
            printf("DIV BX\n");
        }

        printf("MOV %s, AX\n\n", dest);
    }

    return 0;
}