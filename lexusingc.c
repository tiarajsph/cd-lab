#include <stdio.h>
#include <ctype.h>
#include <string.h>

char keywords[][10] = {
    "int", "float", "char", "if", "else", "while", "return"
};

/* Check if word is a keyword */
int isKeyword(char str[])
{
    for (int i = 0; i < 7; i++)
    {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int main()
{
    char input[200], token[50];
    int i = 0, j;

    /* Read statement */
    printf("Enter statement: ");
    fgets(input, sizeof(input), stdin);

    while (input[i] != '\0')
    {
        /* Ignore whitespace */
        if (isspace(input[i]))
        {
            i++;
        }

        /* Keyword or identifier */
        else if (isalpha(input[i]))
        {
            j = 0;

            while (isalnum(input[i]))
                token[j++] = input[i++];

            token[j] = '\0';

            if (isKeyword(token))
                printf("%s : Keyword\n", token);
            else
                printf("%s : Identifier\n", token);
        }

        /* Number */
        else if (isdigit(input[i]))
        {
            j = 0;

            while (isdigit(input[i]))
                token[j++] = input[i++];

            token[j] = '\0';

            printf("%s : Number\n", token);
        }

        /* Operator */
        else if (strchr("+-*/=", input[i]))
        {
            printf("%c : Operator\n", input[i]);
            i++;
        }

        /* Special symbol */
        else if (strchr(";,(){}", input[i]))
        {
            printf("%c : Special Symbol\n", input[i]);
            i++;
        }

        /* Ignore unknown characters */
        else
        {
            i++;
        }
    }

    return 0;
}