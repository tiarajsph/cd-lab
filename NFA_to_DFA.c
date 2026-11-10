
#include <stdio.h>

#define MAX 10

/*
ALGORITHM:

1. Read the number of NFA states and input symbols.
2. Read the input symbols.
3. Read the NFA transition table using bitmask values.
4. Initialize the DFA with the starting state {A}.
5. Process each DFA state:
   a. Find all NFA states present in it.
   b. For each input symbol, find their transitions.
   c. Combine transitions using bitwise OR.
   d. Check whether the resulting DFA state already exists.
   e. If new, add it to the DFA state list.
6. Repeat until all DFA states are processed.
7. Print the equivalent DFA transitions.


PSEUDOCODE:

Read n, m
Read input symbols
Read NFA transition table

dfaStates[0] = 1
front = 0
rear = 1

While front < rear:

    current = dfaStates[front]
    front++

    Print current DFA state

    For each input symbol:

        next = 0

        For each NFA state:
            If state exists in current:
                next = next OR transition[state][symbol]

        Print next DFA state

        If next is not already present:
            Add next to dfaStates

Print all DFA transitions


LOGIC:

- Each NFA state is represented using a bit.
- A = 001, B = 010, C = 100.
- A combination of states is represented by a bitmask.
- Bitwise AND (&) checks whether a state exists.
- Bitwise OR (|) combines destination states.
- front and rear implement a queue-like processing system.
- New DFA states are added until no unprocessed states remain.
- Each unique subset of NFA states becomes one DFA state.

*/



int main()
{
    int n, m;

    printf("Enter number of NFA states: ");
    scanf("%d", &n);

    printf("Enter number of input symbols: ");
    scanf("%d", &m);

    char symbols[MAX];

    printf("Enter input symbols:\n");

    for (int i = 0; i < m; i++)
        scanf(" %c", &symbols[i]);

    int trans[MAX][MAX];

    printf("\nEnter NFA transition table (bitmask values):\n");
    printf("Example: If A -> {A,C}, enter 5 (101 in binary).\n");

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &trans[i][j]);

    int dfaStates[100];
    int front = 0, rear = 0;

    dfaStates[rear++] = 1;

    printf("\nEquivalent DFA:\n");

    while (front < rear)
    {
        int current = dfaStates[front++];

        printf("{ ");

        for (int i = 0; i < n; i++)
            if (current & (1 << i))
                printf("%c ", 'A' + i);

        printf("}");

        for (int s = 0; s < m; s++)
        {
            int next = 0;

            for (int i = 0; i < n; i++)
                if (current & (1 << i))
                    next |= trans[i][s];

            printf(" --%c--> { ", symbols[s]);

            for (int i = 0; i < n; i++)
                if (next & (1 << i))
                    printf("%c ", 'A' + i);

            printf("}");

            int found = 0;

            for (int i = 0; i < rear; i++)
                if (dfaStates[i] == next)
                {
                    found = 1;
                    break;
                }

            if (!found)
                dfaStates[rear++] = next;
        }

        printf("\n");
    }

    return 0;
}

