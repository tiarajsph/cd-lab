#include <stdio.h>
#include <string.h>

#define MAX 20

char p[MAX][30];
int first[26][128], follow[26][128];
int n;

int nt(char c) {
    return c >= 'A' && c <= 'Z';
}

int add(int set[26][128], int x, int c) {
    if (!set[x][c]) {
        set[x][c] = 1;
        return 1;
    }
    return 0;
}

int main() {
    int i, j, k, r, x, y, z;
    int change, nullable;
    int seen[26] = {0};
    char c, s;

    printf("Enter number of productions: ");
    scanf("%d", &n);
    printf("Enter productions (example E=TR, R=#):\n");

    for (i = 0; i < n; i++) 
        scanf("%s", p[i]);

    do {
        change = 0;
        for (i = 0; i < n; i++) {
            x = p[i][0] - 'A';
            nullable = 1;
            for (j = 2; p[i][j] != '\0'; j++) {
                c = p[i][j];
                if (!nt(c)) {
                    change |= add(first, x, c);
                    nullable = 0;
                    break;
                }
                y = c - 'A';
                for (k = 0; k < n; k++) {
                    if (p[k][0] == c) {
                        for (r = 0; r < 128; r++) {
                            if (r != '#' && first[y][r]) 
                                change |= add(first, x, r);
                        }
                    }
                }
                if (!first[y]['#']) {
                    nullable = 0;
                    break;
                }
            }
            if (nullable) 
                change |= add(first, x, '#');
        }
    } while (change);

    follow[p[0][0] - 'A']['$'] = 1;

    do {
        change = 0;
        for (i = 0; i < n; i++) {
            x = p[i][0] - 'A';
            for (j = 2; p[i][j] != '\0'; j++) {
                c = p[i][j];
                if (!nt(c)) 
                    continue;
                y = c - 'A';
                nullable = 1;
                for (k = j + 1; p[i][k] != '\0'; k++) {
                    s = p[i][k];
                    if (!nt(s)) {
                        change |= add(follow, y, s);
                        nullable = 0;
                        break;
                    }
                    z = s - 'A';
                    for (r = 0; r < 128; r++) {
                        if (r != '#' && first[z][r]) 
                            change |= add(follow, y, r);
                    }
                    if (!first[z]['#']) {
                        nullable = 0;
                        break;
                    }
                }
                if (nullable) {
                    for (r = 0; r < 128; r++) {
                        if (follow[x][r]) 
                            change |= add(follow, y, r);
                    }
                }
            }
        }
    } while (change);

    printf("\nFIRST and FOLLOW Sets:\n");

for (i = 0; i < n; i++) {
    x = p[i][0] - 'A';

    if (seen[x])
        continue;
    seen[x] = 1;

    printf("FIRST(%c) = { ", p[i][0]);
    for (j = 0; j < 128; j++)
        if (first[x][j])
            printf("%c ", j);
    printf("}\n");

    printf("FOLLOW(%c) = { ", p[i][0]);
    for (j = 0; j < 128; j++)
        if (follow[x][j])
            printf("%c ", j);
    printf("}\n");
}

return 0;