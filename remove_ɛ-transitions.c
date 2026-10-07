#include <stdio.h>

#define MAX 10

int n, m;

int trans[MAX][MAX];

int epsilon[MAX][MAX];

int closure(int start)
{
    int visited[MAX] = {0};
    int stack[MAX];
    int top = 0;

    stack[top++] = start;
    visited[start] = 1;

    while (top > 0)
    {
        int v = stack[--top];

        for (int i = 0; i < n; i++)
        {
            if (epsilon[v][i] && !visited[i])
            {
                visited[i] = 1;
                stack[top++] = i;
            }
        }
    }

    int result = 0;

    for (int i = 0; i < n; i++)
    {
        if (visited[i])
            result |= (1 << i);
    }

    return result;
}

int main()
{
    char symbols[MAX];
    int e, t;

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter states:\n");

    char states[MAX];

    for (int i = 0; i < n; i++)
        scanf(" %c", &states[i]);

    printf("Enter number of input symbols: ");
    scanf("%d", &m);

    printf("Enter symbols:\n");

    for (int i = 0; i < m; i++)
        scanf(" %c", &symbols[i]);

    printf("Enter number of epsilon transitions: ");
    scanf("%d", &e);

    printf("Enter epsilon transitions (from to):\n");

    for (int i = 0; i < e; i++)
    {
        char a, b;

        scanf(" %c %c", &a, &b);

        int u = a - 'A';
        int v = b - 'A';

        epsilon[u][v] = 1;
    }

    printf("Enter number of transitions: ");
    scanf("%d", &t);

    printf("Enter transitions (from symbol to):\n");

    for (int i = 0; i < t; i++)
    {
        char from, sym, to;

        scanf(" %c %c %c", &from, &sym, &to);

        int u = from - 'A';
        int v = to - 'A';

        int s = 0;

        while (symbols[s] != sym)
            s++;

        trans[u][s] |= (1 << v);
    }

    printf("\nEquivalent NFA without epsilon transitions:\n");

    for (int i = 0; i < n; i++)
    {
        for (int s = 0; s < m; s++)
        {
            int next = 0;

            int c1 = closure(i);

            for (int j = 0; j < n; j++)
            {
                if (c1 & (1 << j))
                {
                    int destinations = trans[j][s];

                    for (int k = 0; k < n; k++)
                    {
                        if (destinations & (1 << k))
                        {
                            next |= closure(k);
                        }
                    }
                }
            }

            printf("%c --%c--> { ", states[i], symbols[s]);

            for (int j = 0; j < n; j++)
            {
                if (next & (1 << j))
                    printf("%c ", states[j]);
            }

            printf("}\n");
        }
    }

    return 0;
}
