
#include <stdio.h>

#define MAX 10

// n = number of states
// m = number of input symbols
int n, m;


// --------------------------------------------------
// TRANSITION TABLE
// --------------------------------------------------

// trans[state][symbol]
//
// Each entry stores the destination states as a BITMASK.
//
// Example for states A, B, C:
//
// A = 001 = 1
// B = 010 = 2
// C = 100 = 4
//
// If A --0--> {A,C}
// then:
//
// trans[A][0] = 001 | 100
//              = 101
//              = 5
//
int trans[MAX][MAX];


// --------------------------------------------------
// EPSILON TRANSITION TABLE
// --------------------------------------------------

// epsilon[i][j] = 1 means:
//
// i --ε--> j
//
// epsilon[i][j] = 0 means there is no ε-transition.
int epsilon[MAX][MAX];


// --------------------------------------------------
// FIND ε-CLOSURE
// --------------------------------------------------

// ε-closure(start) means:
//
// "All states that can be reached from 'start'
//  by following ONLY ε-transitions."
//
// Example:
//
// A --ε--> B
// B --ε--> C
//
// ε-closure(A) = {A,B,C}
//
// The function returns this set as a BITMASK.
int closure(int start)
{
    // visited[i] tells us whether state i
    // has already been reached.
    //
    // Initially everything is 0.
    int visited[MAX] = {0};


    // Stack is used to explore states.
    //
    // Whenever we discover a new state through ε,
    // we put it into the stack.
    int stack[MAX];


    // top tells us where the next item
    // will be inserted in the stack.
    int top = 0;


    // Start the search from the given state.
    stack[top++] = start;

    // The starting state is always part
    // of its own ε-closure.
    visited[start] = 1;


    // Continue while there are states
    // waiting to be explored.
    while (top > 0)
    {
        // Take one state from the stack.
        int v = stack[--top];


        // Check every possible state.
        for (int i = 0; i < n; i++)
        {
            // Is there an ε-transition:
            //
            // v --ε--> i
            //
            // AND have we not visited i yet?
            if (epsilon[v][i] && !visited[i])
            {
                // Mark i as reachable.
                visited[i] = 1;

                // Put i into the stack so that
                // we can also follow ε-transitions
                // from i.
                stack[top++] = i;
            }
        }
    }


    // --------------------------------------------------
    // CONVERT THE CLOSURE INTO A BITMASK
    // --------------------------------------------------

    // Initially, no states are included.
    int result = 0;


    for (int i = 0; i < n; i++)
    {
        // If state i belongs to the closure...
        if (visited[i])
        {
            // Add state i to the bitmask.
            //
            // 1 << i creates the bit corresponding
            // to state i.
            //
            // result |= combines it with the
            // states already present.
            result |= (1 << i);
        }
    }


    // Return the ε-closure as a bitmask.
    return result;
}


int main()
{
    // Stores the input symbols.
    // Example: 0, 1
    char symbols[MAX];


    // e = number of ε-transitions
    // t = number of normal transitions
    int e, t;


    // --------------------------------------------------
    // INPUT NUMBER OF STATES
    // --------------------------------------------------

    printf("Enter number of states: ");
    scanf("%d", &n);


    // --------------------------------------------------
    // INPUT STATE NAMES
    // --------------------------------------------------

    printf("Enter states:\n");

    char states[MAX];

    for (int i = 0; i < n; i++)
    {
        scanf(" %c", &states[i]);
    }


    // --------------------------------------------------
    // INPUT NUMBER OF SYMBOLS
    // --------------------------------------------------

    printf("Enter number of input symbols: ");
    scanf("%d", &m);


    // Read the actual symbols.
    //
    // Example:
    // 0
    // 1
    printf("Enter symbols:\n");

    for (int i = 0; i < m; i++)
    {
        scanf(" %c", &symbols[i]);
    }


    // --------------------------------------------------
    // INPUT ε-TRANSITIONS
    // --------------------------------------------------

    printf("Enter number of epsilon transitions: ");
    scanf("%d", &e);


    printf("Enter epsilon transitions (from to):\n");

    for (int i = 0; i < e; i++)
    {
        char a, b;

        // Read:
        //
        // A B
        //
        // meaning:
        //
        // A --ε--> B
        scanf(" %c %c", &a, &b);


        // Convert state letters to array indexes.
        //
        // A → 0
        // B → 1
        // C → 2
        //
        // 'B' - 'A' = 1
        int u = a - 'A';
        int v = b - 'A';


        // Record the ε-transition.
        //
        // u --ε--> v
        epsilon[u][v] = 1;
    }


    // --------------------------------------------------
    // INPUT NORMAL TRANSITIONS
    // --------------------------------------------------

    printf("Enter number of transitions: ");
    scanf("%d", &t);


    printf("Enter transitions (from symbol to):\n");

    for (int i = 0; i < t; i++)
    {
        char from, sym, to;


        // Example input:
        //
        // A 0 C
        //
        // means:
        //
        // A --0--> C
        scanf(" %c %c %c", &from, &sym, &to);


        // Convert source and destination
        // state names into indexes.
        int u = from - 'A';
        int v = to - 'A';


        // Find which position the symbol
        // occupies in the symbols array.
        //
        // Example:
        //
        // symbols = {0, 1}
        //
        // symbol '0' → s = 0
        // symbol '1' → s = 1
        int s = 0;

        while (symbols[s] != sym)
        {
            s++;
        }


        // Add destination v to the transition set.
        //
        // 1 << v represents state v.
        //
        // |= combines it with destinations
        // already present.
        //
        // This allows multiple destinations.
        //
        // Example:
        //
        // A --0--> A
        // A --0--> C
        //
        // gives:
        //
        // trans[A][0] = A | C
        //              = 001 | 100
        //              = 101
        trans[u][s] |= (1 << v);
    }


    // --------------------------------------------------
    // CONVERT ε-NFA → NFA
    // --------------------------------------------------

    printf("\nEquivalent NFA without epsilon transitions:\n");


    // Take every state as the starting state.
    for (int i = 0; i < n; i++)
    {

        // Take every input symbol.
        for (int s = 0; s < m; s++)
        {

            // 'next' stores the final destination set
            // of the new NFA.
            //
            // Start with an empty set.
            int next = 0;


            // --------------------------------------------------
            // STEP 1:
            // Find ε-closure of the current state
            // --------------------------------------------------

            // Example:
            //
            // A --ε--> B
            // B --ε--> C
            //
            // closure(A) = {A,B,C}
            int c1 = closure(i);


            // --------------------------------------------------
            // STEP 2:
            // Check every state in the ε-closure
            // --------------------------------------------------

            for (int j = 0; j < n; j++)
            {
                // Check whether state j is present
                // in the closure.
                //
                // c1 & (1 << j)
                //
                // asks:
                // "Is j part of the set c1?"
                if (c1 & (1 << j))
                {

                    // --------------------------------------------------
                    // STEP 3:
                    // Follow the actual input symbol
                    // --------------------------------------------------

                    // Get all destinations of state j
                    // on input symbol s.
                    //
                    // This is also a bitmask.
                    int destinations = trans[j][s];


                    // Check every possible destination.
                    for (int k = 0; k < n; k++)
                    {
                        // Is state k one of the destinations?
                        if (destinations & (1 << k))
                        {

                            // --------------------------------------------------
                            // STEP 4:
                            // Take ε-closure of the destination
                            // --------------------------------------------------

                            // Whatever states are reachable from k
                            // using ε-transitions are also part
                            // of our final destination set.
                            //
                            // |= combines this closure with
                            // everything already found.
                            next |= closure(k);
                        }
                    }
                }
            }


            // --------------------------------------------------
            // PRINT THE RESULT
            // --------------------------------------------------

            // Print:
            //
            // A --0--> {
            printf("%c --%c--> { ", states[i], symbols[s]);


            // Convert the final bitmask back into
            // state names for display.
            for (int j = 0; j < n; j++)
            {
                // Is state j present in 'next'?
                if (next & (1 << j))
                {
                    // Print its state name.
                    printf("%c ", states[j]);
                }
            }


            printf("}\n");
        }
    }


    return 0;
}