
/*
ALGORITHM:

1. Read the number of productions and grammar rules.
2. Identify nonterminals using uppercase letters.
3. Calculate FIRST sets:
   a. If the symbol is a terminal, add it to FIRST.
   b. If it is a nonterminal, copy its FIRST set except epsilon.
   c. If it contains epsilon, check the next symbol.
   d. If all symbols can produce epsilon, add '#'.
   e. Repeat until no changes occur.
4. Add '$' to FOLLOW of the start symbol.
5. Calculate FOLLOW sets:
   a. Find every nonterminal in the RHS.
   b. Check the symbols following it.
   c. Add FIRST of those symbols except '#'.
   d. If the remaining symbols can produce epsilon,
      add FOLLOW of the LHS.
   e. Repeat until no changes occur.
6. Print FIRST and FOLLOW sets.


PSEUDOCODE:

START
    Read productions

    REPEAT
        FOR each production
            Find FIRST of RHS
            Add FIRST symbols to LHS
        UNTIL no changes

    Add '$' to FOLLOW of start symbol

    REPEAT
        FOR each nonterminal in RHS
            Find symbols after it
            Add their FIRST except '#'
            IF remaining symbols can produce epsilon
                Add FOLLOW of LHS
        UNTIL no changes

    Print FIRST and FOLLOW
END


CORE LOGIC:

- p[][] stores grammar productions.
- first[][] stores FIRST sets.
- follow[][] stores FOLLOW sets.
- # represents epsilon.
- $ represents end of input.
- nt() checks whether a character is a nonterminal.
- addF() adds a symbol to FIRST.
- addW() adds a symbol to FOLLOW.
- change indicates whether any new symbol was added.
- nullable checks whether the remaining symbols can
  produce epsilon.
- seen[] prevents printing the same nonterminal twice.


LINE-BY-LINE EXPLANATION:
*/


/*
ALGORITHM:
1. Read the number of productions and grammar rules.
2. Identify nonterminals using uppercase letters.
3. For each production:
   a. Check the RHS from left to right.
   b. If a terminal is found, add it to FIRST.
   c. If a nonterminal is found, copy its FIRST except '#'.
   d. If it contains '#', check the next symbol.
   e. If all symbols produce '#', add '#' to FIRST.
4. Repeat until no changes occur.
5. Print FIRST sets.

PSEUDOCODE:
START
    Read productions
    REPEAT
        FOR each production
            Check RHS symbols
            Add terminals to FIRST
            Copy FIRST of nonterminals
            Continue if epsilon exists
        UNTIL no changes
    Print FIRST sets
END

CORE LOGIC:
- p[][] stores productions.
- first[][] stores FIRST sets.
- # represents epsilon.
- nt() checks for nonterminals.
- addF() adds a symbol to FIRST.
- change repeats calculation until stable.
*/

// Header file
#include <stdio.h>
#define MAX 20

// Store productions and FIRST sets
char p[MAX][30];
int first[26][128];
int n;

// Check whether symbol is a nonterminal
int nt(char c) {
    return c >= 'A' && c <= 'Z';
}

// Add symbol to FIRST
int addF(int x, int c) {
    if (first[x][c]) return 0;
    first[x][c] = 1;
    return 1;
}

int main() {
    int i, j, k, x, y, change, nullable;
    char c;
    int seen[26] = {0};

    // Read productions
    printf("Enter number of productions: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
        scanf("%s", p[i]);

    // FIND FIRST
    do {
        change = 0;

        // Check every production
        for (i = 0; i < n; i++) {

            // LHS nonterminal
            x = p[i][0] - 'A';
            nullable = 1;

            // Check RHS from index 2
            for (j = 2; p[i][j]; j++) {
                c = p[i][j];

                // Skip epsilon
                if (c == '#') continue;

                // If terminal, add and stop
                if (!nt(c)) {
                    change |= addF(x, c);
                    nullable = 0;
                    break;
                }

                // Get nonterminal index
                y = c - 'A';

                // Copy FIRST except epsilon
                for (k = 0; k < 128; k++)
                    if (k != '#' && first[y][k])
                        change |= addF(x, k);

                // Continue only if epsilon exists
                if (!first[y]['#']) {
                    nullable = 0;
                    break;
                }
            }

            // Add epsilon if all symbols are nullable
            if (nullable)
                change |= addF(x, '#');
        }

    } while (change);

    // PRINT FIRST SETS
    for (i = 0; i < n; i++) {
        x = p[i][0] - 'A';

        // Avoid duplicate printing
        if (seen[x]) continue;
        seen[x] = 1;

        printf("\nFIRST(%c) = { ", p[i][0]);

        for (j = 0; j < 128; j++)
            if (first[x][j])
                printf("%c ", j);

        printf("}\n");
    }

    return 0;
}
