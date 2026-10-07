#include <stdio.h>
#include <string.h>

#define MAX 20

int n;

char states[MAX][10];
int epsilon[MAX][MAX];
int visited[MAX];


/* Find the index of a state */
int getIndex(char state[])
{
    for (int i = 0; i < n; i++)
    {
        if (strcmp(states[i], state) == 0)
            return i;
    }

    return -1;
}


/* Find epsilon-closure using DFS */
void dfs(int v)
{
    visited[v] = 1;       // Mark current state as visited

    for (int i = 0; i < n; i++)
    {
        /*
           If there is an epsilon transition
           from v to i, and i is not visited,
           follow it.
        */
        if (epsilon[v][i] && !visited[i])
        {
            dfs(i);
        }
    }
}


int main()
{
    int e;
    char from[10], to[10];


    /* Read number of states */

    printf("Enter number of states: ");
    scanf("%d", &n);


    /* Read state names */

    printf("Enter state names:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%s", states[i]);
    }


    /*
       Initially there are no epsilon transitions.
       So set the whole matrix to 0.
    */

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            epsilon[i][j] = 0;
        }
    }


    /* Read epsilon transitions */

    printf("Enter number of epsilon transitions: ");
    scanf("%d", &e);

    printf("Enter epsilon transitions (from to):\n");

    for (int i = 0; i < e; i++)
    {
        scanf("%s %s", from, to);

        int u = getIndex(from);
        int v = getIndex(to);

        epsilon[u][v] = 1;
    }


    /* Find epsilon-closure of every state */

    printf("\nEpsilon Closures:\n");

    for (int i = 0; i < n; i++)
    {
        /*
           Clear visited before finding
           the closure of a new state.
        */
        memset(visited, 0, sizeof(visited));

        dfs(i);

        printf("ε-closure(%s) = { ", states[i]);

        /* Print all states reached by DFS */

        for (int j = 0; j < n; j++)
        {
            if (visited[j])
            {
                printf("%s ", states[j]);
            }
        }

        printf("}\n");
    }

    return 0;
}