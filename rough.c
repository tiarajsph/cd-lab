#include <stdio.h>

#define MAX 10

// trans[i][0] = state reached from i on input 0
// trans[i][1] = state reached from i on input 1
int trans[MAX][2];

// final[i] = 1 → state i is final
// final[i] = 0 → state i is non-final
int final[MAX];

// mark[i][j] = 1 → states i and j are different
// mark[i][j] = 0 → not known to be different
int mark[MAX][MAX];


int main()
{
    int n;

    // Loop variables
    int i, j, k;

    // Used to check whether a new pair was marked
    int change;


    // -------------------------------
    // STEP 1: INPUT
    // -------------------------------

    // Read number of states
    printf("Enter number of states: ");
    scanf("%d", &n);


    // Read DFA transition table
    printf("\nEnter transition table\n");

    for(i = 0; i < n; i++)
    {
        printf("\nState %d\n", i);

        // Destination of state i on input 0
        printf("On input 0: ");
        scanf("%d", &trans[i][0]);

        // Destination of state i on input 1
        printf("On input 1: ");
        scanf("%d", &trans[i][1]);
    }


    // Read which states are final
    // 1 = final
    // 0 = non-final
    printf("\nEnter 1 if final state else 0\n");

    for(i = 0; i < n; i++)
    {
        printf("State %d : ", i);
        scanf("%d", &final[i]);
    }


    // -------------------------------
    // STEP 2: INITIALIZE MARK TABLE
    // -------------------------------

    // Initially, assume no pair is different.
    // Therefore, put 0 everywhere.
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            mark[i][j] = 0;
        }
    }


    // -------------------------------
    // STEP 3: INITIAL MARKING
    // -------------------------------

    // A final state and a non-final state
    // can NEVER be equivalent.
    //
    // So mark every final/non-final pair.
    for(i = 0; i < n; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            // If one is final and the other isn't
            if(final[i] != final[j])
            {
                // Mark them as different
                mark[i][j] = 1;
            }
        }
    }


    // -------------------------------
    // STEP 4: KEEP MARKING PAIRS
    // -------------------------------

    // We repeat until no new pair gets marked.
    do
    {
        // Assume no new pair will be marked
        // during this round.
        change = 0;


        // Check every pair of states
        for(i = 0; i < n; i++)
        {
            for(j = i + 1; j < n; j++)
            {
                // Only check pairs that are
                // not already marked.
                if(mark[i][j] == 0)
                {

                    // Check both input symbols:
                    // k = 0 → input 0
                    // k = 1 → input 1
                    for(k = 0; k < 2; k++)
                    {

                        // Where does state i go
                        // on input k?
                        int a = trans[i][k];

                        // Where does state j go
                        // on input k?
                        int b = trans[j][k];


                        // mark[][] only stores pairs
                        // in smaller-number-first order.
                        //
                        // Example:
                        // a = 3, b = 1
                        // becomes a = 1, b = 3
                        if(a > b)
                        {
                            int temp = a;
                            a = b;
                            b = temp;
                        }


                        // If the destination states
                        // are already known to be different,
                        // then i and j must also be different.
                        //
                        // Example:
                        // i --0--> a
                        // j --0--> b
                        //
                        // If a and b are different,
                        // then i and j are different.
                        if(mark[a][b] == 1)
                        {
                            // Mark current pair as different
                            mark[i][j] = 1;

                            // A new marking happened
                            change = 1;

                            // No need to check the other
                            // input symbol for this pair.
                            break;
                        }
                    }
                }
            }
        }

    // If change = 1, another round is needed.
    // If change = 0, no new pairs were marked,
    // so we are finished.
    } while(change);


    // -------------------------------
    // STEP 5: PRINT EQUIVALENT STATES
    // -------------------------------

    printf("\nEquivalent States\n\n");

    for(i = 0; i < n; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            // If the pair was NEVER marked,
            // the states are equivalent.
            if(mark[i][j] == 0)
            {
                printf("(%d , %d)\n", i, j);
            }
        }
    }


    return 0;
}