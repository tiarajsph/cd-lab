
#include <stdio.h>

int main()
{
    int n;
    char dest[10], a[10], b[10], op;

    printf("Enter number of instructions: ");
    scanf("%d", &n);

    printf("Enter the three address code:\n");
    printf("Generated 8086 Assembly Code:\n\n");

    while (n--) {
        scanf("%9s = %9s %c %9s", dest, a, &op, b);

        printf("MOV AX, %s\n", a);

        switch (op) {
            case '+': printf("ADD AX, %s\n", b); break;
            case '-': printf("SUB AX, %s\n", b); break;
            case '*': printf("MOV BX, %s\nMUL BX\n", b); break;
            case '/': printf("MOV BX, %s\nXOR DX, DX\nDIV BX\n", b); break;
        }

        printf("MOV %s, AX\n\n", dest);
    }

    return 0;
}

/*
ALGORITHM:
1. Read the number of three address instructions.
2. For each instruction:
   a. Read destination, first operand, operator and second operand.
   b. Move the first operand into AX.
   c. Check the operator:
      - '+' : ADD AX, second operand
      - '-' : SUB AX, second operand
      - '*' : Move second operand to BX and MUL BX
      - '/' : Move second operand to BX, clear DX and DIV BX
   d. Move the result from AX to destination.
3. Repeat for all instructions.

PSEUDOCODE:
START
    Read n

    WHILE n > 0
        Read dest, a, operator, b

        PRINT MOV AX, a

        SWITCH operator
            CASE '+': PRINT ADD AX, b
            CASE '-': PRINT SUB AX, b
            CASE '*':
                PRINT MOV BX, b
                PRINT MUL BX
            CASE '/':
                PRINT MOV BX, b
                PRINT XOR DX, DX
                PRINT DIV BX

        PRINT MOV dest, AX
        n = n - 1
    END WHILE

END

CORE LOGIC:
- dest stores the result variable.
- a stores the first operand.
- b stores the second operand.
- op stores the arithmetic operator.
- AX is used to hold the first operand and result.
- BX is used for multiplication and division.
- DX is cleared before unsigned division.
- switch(op) selects the corresponding assembly instruction.
- The result is stored in the destination variable.

INPUT SIMULATION:

Input:
3
t1 = a + b
t2 = c * d
t3 = t1 - t2

Execution:

Instruction 1:
dest = t1, a = a, op = +, b = b
MOV AX, a
ADD AX, b
MOV t1, AX

Instruction 2:
dest = t2, a = c, op = *, b = d
MOV AX, c
MOV BX, d
MUL BX
MOV t2, AX

Instruction 3:
dest = t3, a = t1, op = -, b = t2
MOV AX, t1
SUB AX, t2
MOV t3, AX

OUTPUT:
MOV AX, a
ADD AX, b
MOV t1, AX

MOV AX, c
MOV BX, d
MUL BX
MOV t2, AX

MOV AX, t1
SUB AX, t2
MOV t3, AX
*/