
/*
ALGORITHM:
1. Read states and input symbols.
2. Read epsilon transitions.
3. Read normal transitions.
4. Find epsilon closure of every state.
5. For each state and input symbol:
   a. Find its epsilon closure.
   b. Find normal transitions from those states.
   c. Find epsilon closure of every destination.
6. Print the new transitions.

PSEUDOCODE:
START
    Read states and symbols
    Read epsilon transitions
    Read normal transitions

    Add each state to its own closure
    Find all epsilon closures

    FOR each state
        FOR each input symbol
            Find epsilon closure
            Find normal destinations
            Find destination closures
            Print new transition
END

CORE LOGIC:
- eps[][] stores epsilon transitions and closures.
- trans[][][] stores normal transitions.
- next[] stores final destination states.
- eps[i][j] = 1 means j belongs to closure of i.

OUTPUT SIMULATION:

INPUT:
3
A B C
1
a
2
A B
B C
2
B a B
C a C

STEP 1: Epsilon transitions:
A -> B
B -> C

STEP 2: Epsilon closures:
Closure(A) = {A, B, C}
Closure(B) = {B, C}
Closure(C) = {C}

STEP 3: Normal transitions:
B --a--> B
C --a--> C

STEP 4: Find new transition for A on a:
Closure(A) = {A, B, C}
From B on a -> B
From C on a -> C

Closure(B) = {B, C}
Closure(C) = {C}

Therefore:
A --a--> {B, C}

Similarly:
B --a--> {B, C}
C --a--> {C}

EXPECTED OUTPUT:
Equivalent NFA without epsilon transitions:
A --a--> { B C }
B --a--> { B C }
C --a--> { C }
*/

#include <stdio.h>
#define MAX 10

int n, m;

// Epsilon closure matrix
int eps[MAX][MAX];

// Normal transition matrix : trans[from][symbol][to] = 1;
int trans[MAX][MAX][MAX];

int main()
{
    char states[MAX], symbols[MAX];
    int e, t, i, j, k, s, l;
    int next[MAX];

    // Read states
    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter states:\n");
    for (i = 0; i < n; i++)
        scanf(" %c", &states[i]);

    // Read input symbols
    printf("Enter number of input symbols: ");
    scanf("%d", &m);

    printf("Enter symbols:\n");
    for (i = 0; i < m; i++)
        scanf(" %c", &symbols[i]);

    // Read epsilon transitions
    printf("Enter number of epsilon transitions: ");
    scanf("%d", &e);

    printf("Enter epsilon transitions (from to):\n");

    for (i = 0; i < e; i++)
    {
        char a, b;
        scanf(" %c %c", &a, &b);

        eps[a - 'A'][b - 'A'] = 1;
    }

    // Read normal transitions
    printf("Enter number of transitions: ");
    scanf("%d", &t);

    printf("Enter transitions (from symbol to):\n");

    for (i = 0; i < t; i++)
    {
        char a, b, c;
        scanf(" %c %c %c", &a, &b, &c);

        // Find symbol index
        s = 0;
        while (symbols[s] != b)
            s++;

        trans[a - 'A'][s][c - 'A'] = 1;
    }

    // Add each state to its own epsilon closure
    for (i = 0; i < n; i++)
        eps[i][i] = 1;

    // Find all epsilon closures
    for (k = 0; k < n; k++)
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                if (eps[i][k] && eps[k][j])
                    eps[i][j] = 1;

    // Print equivalent NFA
    printf("\nEquivalent NFA without epsilon transitions:\n");

    for (i = 0; i < n; i++)
    {
        for (s = 0; s < m; s++)
        {
            // Clear destination states
            for (j = 0; j < n; j++)
                next[j] = 0;

            // Check epsilon closure of current state
            for (j = 0; j < n; j++)
            {
                if (eps[i][j])
                {
                    // Find normal transitions
                    for (k = 0; k < n; k++)
                    {
                        if (trans[j][s][k])
                        {
                            // Add epsilon closure of destination
                            for (l = 0; l < n; l++)
                            {
                                if (eps[k][l])
                                    next[l] = 1;
                            }
                        }
                    }
                }
            }

            // Print new transition
            printf("%c --%c--> { ", states[i], symbols[s]);

            for (j = 0; j < n; j++)
                if (next[j])
                    printf("%c ", states[j]);

            printf("}\n");
        }
    }

    return 0;
}
