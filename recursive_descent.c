#include <stdio.h>    // For printf() and scanf()
#include <string.h>   // For strcat()

char in[100];         // Stores the input expression
int pos = 0;          // Points to the current character
int error = 0;        // Becomes 1 if an error is found

void E();             // Function declarations
void T();
void F();

/* E handles expressions containing + */
void E()
{
    T();              // First, process a term

    // Continue as long as the next symbol is +
    while (in[pos] == '+' && !error)
    {
        pos++;        // Consume +
        T();          // Process the term after +
    }
}

/* T handles terms containing * */
void T()
{
    F();              // First, process a factor

    // Continue as long as the next symbol is *
    while (in[pos] == '*' && !error)
    {
        pos++;        // Consume *
        F();          // Process the factor after *
    }
}

/* F handles identifiers and parenthesized expressions */
void F()
{
    // If the current symbol is i, it is an identifier
    if (in[pos] == 'i')
    {
        pos++;        // Consume i
    }
    // If the current symbol is (, process an expression inside it
    else if (in[pos] == '(')
    {
        pos++;        // Consume (

        E();          // Parse the expression inside parentheses

        // Check whether the expression ends with )
        if (in[pos] == ')')
            pos++;    // Consume )
        else
            error = 1; // Missing closing parenthesis
    }
    // Any other symbol is invalid here
    else
    {
        error = 1;
    }
}

int main()
{
    printf("Enter expression (use i for identifier): ");

    scanf("%98s", in);   // Read the expression

    strcat(in, "$");     // Append $ to mark the end of input

    E();                 // Start parsing from the expression rule

    // Accept only if there were no errors and input is fully consumed
    if (!error && in[pos] == '$')
        printf("Expression Accepted\n");
    else
        printf("Expression Rejected\n");

    return 0;            // End program successfully
}