
#include <stdio.h>
#define MAX 10

/*
ALGORITHM:
1. Read number of states.
2. Read transition table for inputs 0 and 1.
3. Read final/non-final status of each state.
4. Initially mark pairs where one is final and the other is non-final.
5. Check unmarked pairs:
   - Find their destination states for each input.
   - If the destination pair is already marked,
     mark the original pair.
6. Repeat until no new pairs are marked.
7. Print all unmarked pairs as equivalent states.

PSEUDOCODE:

Read n
Read transition table
Read final states

Initialize mark[][] = 0

For each pair (i,j):
    If final[i] != final[j]:
        mark[i][j] = 1

Repeat:
    change = 0

    For each unmarked pair (i,j):
        For each input k:
            a = trans[i][k]
            b = trans[j][k]

            Arrange a,b in ascending order

            If mark[a][b] == 1:
                Mark pair (i,j)
                change = 1

Until change = 0

Print all unmarked pairs.

LOGIC:
- mark[i][j] = 1 means distinguishable.
- mark[i][j] = 0 means potentially equivalent.
- Final and non-final states are always distinguishable.
- If two states reach a distinguishable pair
  on the same input, they are distinguishable.
- Repeat until no new pairs are marked.
*/

int trans[MAX][2], final[MAX], mark[MAX][MAX];

int main()
{
    int n, i, j, k, change;

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("\nEnter transition table\n");

    for(i = 0; i < n; i++)
    {
        printf("\nState %d\n", i);
        printf("On input 0: ");
        scanf("%d", &trans[i][0]);
        printf("On input 1: ");
        scanf("%d", &trans[i][1]);
    }

    printf("\nEnter 1 if final state else 0\n");

    for(i = 0; i < n; i++)
    {
        printf("State %d : ", i);
        scanf("%d", &final[i]);
    }

    // Mark final and non-final pairs

    for(i = 0; i < n; i++)
        for(j = i + 1; j < n; j++)
            if(final[i] != final[j])
                mark[i][j] = 1;

    // Repeat until no new pairs are marked

    do
    {
        change = 0;

        for(i = 0; i < n; i++)
        {
            for(j = i + 1; j < n; j++)
            {
                if(!mark[i][j])
                {
                    for(k = 0; k < 2; k++)
                    {
                        int a = trans[i][k];
                        int b = trans[j][k];

                        if(a > b)
                        {
                            int temp = a;
                            a = b;
                            b = temp;
                        }

                        if(mark[a][b])
                        {
                            mark[i][j] = 1;
                            change = 1;
                            break;
                        }
                    }
                }
            }
        }

    } while(change);

    printf("\nEquivalent States\n\n");

    for(i = 0; i < n; i++)
        for(j = i + 1; j < n; j++)
            if(!mark[i][j])
                printf("(%d , %d)\n", i, j);

    return 0;
}