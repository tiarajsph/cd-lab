
#include <stdio.h>
#define MAX 20

/*
ALGORITHM:
1. Read number of states and epsilon transition matrix.
2. Read the starting state.
3. Mark the starting state as visited.
4. Find all states reachable through epsilon transitions.
5. Recursively visit unvisited states.
6. Print all visited states.

PSEUDOCODE:
closure(s):
    visited[s] = 1
    for each state i:
        if a[s][i] == 1 AND visited[i] == 0:
            closure(i)

main:
    Read n and transition matrix
    Read starting state
    Call closure(start)
    Print all visited states

LOGIC:
- a[s][i] = 1 means an epsilon transition exists.
- visited[] prevents repeated visits.
- Recursion finds directly and indirectly reachable states.
*/

int n, a[MAX][MAX], visited[MAX];

void closure(int s)
{
    visited[s] = 1;

    for (int i = 0; i < n; i++)
        if (a[s][i] && !visited[i])
            closure(i);
}

int main()
{
    int start;

    printf("Enter the number of states: ");
    scanf("%d", &n);

    printf("Enter the epsilon transition matrix (%d x %d):\n", n, n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &a[i][j]);

    printf("Enter the state to find epsilon-closure (0 to %d): ", n - 1);
    scanf("%d", &start);

    closure(start);

    printf("Epsilon-closure of state %d: { ", start);

    for (int i = 0; i < n; i++)
        if (visited[i])
            printf("%d ", i);

    printf("}\n");

    return 0;
}
