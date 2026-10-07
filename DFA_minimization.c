#include <stdio.h>

#define MAX 10

int trans[MAX][2];
int final[MAX];
int mark[MAX][MAX];

int main()
{
    int n;
    int i, j, k;
    int change;

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

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
            mark[i][j] = 0;
    }

    /* Step 1 : Mark Final and Non-final pairs */

    for(i = 0; i < n; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            if(final[i] != final[j])
                mark[i][j] = 1;
        }
    }

    /* Step 2 : Repeat until no new markings */

    do
    {
        change = 0;

        for(i = 0; i < n; i++)
        {
            for(j = i + 1; j < n; j++)
            {
                if(mark[i][j] == 0)
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

                        if(mark[a][b] == 1)
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
    {
        for(j = i + 1; j < n; j++)
        {
            if(mark[i][j] == 0)
            {
                printf("(%d , %d)\n", i, j);
            }
        }
    }

    return 0;
}