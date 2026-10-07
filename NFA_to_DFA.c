#include <stdio.h>

#define MAX 10

int main()
{
    int n, m;

    // n = number of NFA states
    // m = number of input symbols

    printf("Enter number of NFA states: ");
    scanf("%d", &n);

    printf("Enter number of input symbols: ");
    scanf("%d", &m);


    // Store the input symbols
    // Example: 0 1
    char symbols[MAX];

    printf("Enter input symbols:\n");

    for (int i = 0; i < m; i++)
    {
        scanf(" %c", &symbols[i]);
    }


    // trans[i][j] stores the NFA transition
    //
    // i = current NFA state
    // j = input symbol
    //
    // The transition is stored as a BITMASK.
    //
    // States:
    // A = 001 = 1
    // B = 010 = 2
    // C = 100 = 4
    //
    // Therefore:
    // AB = 011 = 3
    // AC = 101 = 5
    // BC = 110 = 6
    // ABC = 111 = 7

    int trans[MAX][MAX];

    printf("\nEnter NFA transition table (bitmask values):\n");

    printf("Example: If A -> {A,C}, enter 5 (101 in binary).\n");


    // Read all NFA transitions

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &trans[i][j]);
        }
    }


    // dfaStates[] stores all DFA states.
    //
    // Each DFA state is represented by one integer.
    //
    // Example:
    // 1 = {A}
    // 3 = {A,B}
    // 5 = {A,C}
    // 7 = {A,B,C}

    int dfaStates[100];

    // front = points to the DFA state currently being processed
    // rear  = position where a new DFA state is added

    int front = 0;
    int rear = 0;


    // Initial DFA state is {A}
    //
    // A = 001 in binary = 1

    dfaStates[rear++] = 1;


    printf("\nEquivalent DFA:\n");


    // Keep processing DFA states until there are no new states.
    //
    // New DFA states are added to dfaStates[]
    // while this loop is running.

    while (front < rear)
    {
        // Get the current DFA state

        int current = dfaStates[front++];


        // Print the current DFA state

        printf("{ ");

        for (int i = 0; i < n; i++)
        {
            // (1 << i) creates the bit corresponding to state i.
            //
            // Example:
            // i = 0 -> 001
            // i = 1 -> 010
            // i = 2 -> 100
            //
            // '&' checks whether that state is present.

            if (current & (1 << i))
            {
                printf("%c ", 'A' + i);
            }
        }

        printf("}");


        // Find transition for every input symbol

        for (int s = 0; s < m; s++)
        {
            // next will store the new DFA state

            int next = 0;


            // Check every NFA state

            for (int i = 0; i < n; i++)
            {
                // Check whether state i is present
                // in the current DFA state.

                if (current & (1 << i))
                {
                    // Add all destinations of state i
                    // for the current input symbol.
                    //
                    // '|' combines the destination sets.

                    next |= trans[i][s];
                }
            }


            // Print the resulting DFA transition

            printf(" --%c--> { ", symbols[s]);

            for (int i = 0; i < n; i++)
            {
                // Check which states are present in 'next'

                if (next & (1 << i))
                {
                    printf("%c ", 'A' + i);
                }
            }

            printf("}");


            // Check whether this DFA state is already present

            int found = 0;

            for (int i = 0; i < rear; i++)
            {
                if (dfaStates[i] == next)
                {
                    found = 1;
                    break;
                }
            }


            // If this is a new DFA state,
            // add it to the list.

            if (!found)
            {
                dfaStates[rear++] = next;
            }
        }

        printf("\n");
    }


    return 0;
}