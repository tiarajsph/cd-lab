
/*
ALGORITHM:
1. Read a statement.
2. Scan the statement character by character.
3. Ignore spaces.
4. If a letter is found, collect the word.
5. Check whether the word is a keyword or identifier.
6. If a digit is found, collect the number.
7. Identify operators and special symbols.
8. Print each token and its type.

PSEUDOCODE:
START
    Read input
    WHILE input is not over
        IF space, skip
        ELSE IF letter
            Collect word
            IF keyword, print Keyword
            ELSE print Identifier
        ELSE IF digit
            Collect number
            Print Number
        ELSE IF operator
            Print Operator
        ELSE IF special symbol
            Print Special Symbol
        ELSE skip
    END WHILE
END

CORE LOGIC:
- isalpha() checks letters.
- isdigit() checks digits.
- isalnum() checks letters or digits.
- strcmp() compares strings.
- token[] stores the current word or number.
- i moves through the input.
- j stores characters in token.
*/

// Header files
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// List of keywords
char keywords[][10] = {
    "int", "float", "char", "if",
    "else", "while", "return"
};

// Check whether a word is a keyword
int isKeyword(char str[]) {
    int i;

    for (i = 0; i < 7; i++) {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }

    return 0;
}

int main() {

    // Input and token storage
    char input[200], token[50];

    // i scans input, j builds token
    int i = 0, j;

    // Read statement
    printf("Enter statement: ");
    fgets(input, 200, stdin);

    // Scan until end of input
    while (input[i] != '\0') {

        // Ignore spaces
        if (isspace(input[i])) {
            i++;
        }

        // Check for a word (keyword or identifier)
        else if (isalpha(input[i])) {
            j = 0;

            // Collect letters and digits
            while (isalnum(input[i])) {
                token[j] = input[i];
                j++;
                i++;
            }

            // End the string
            token[j] = '\0';

            // Check whether it is a keyword
            if (isKeyword(token))
                printf("%s : Keyword\n", token);
            else
                printf("%s : Identifier\n", token);
        }

        // Check for a number
        else if (isdigit(input[i])) {
            j = 0;

            // Collect digits
            while (isdigit(input[i])) {
                token[j] = input[i];
                j++;
                i++;
            }

            // End the string
            token[j] = '\0';

            printf("%s : Number\n", token);
        }

        // Check for operators
        else if (strchr("+-*/=", input[i])) {
            printf("%c : Operator\n", input[i]);
            i++;
        }

        // Check for special symbols
        else if (strchr(";,(){}", input[i])) {
            printf("%c : Special Symbol\n", input[i]);
            i++;
        }

        // Skip unknown characters
        else {
            i++;
        }
    }

    return 0;
}
