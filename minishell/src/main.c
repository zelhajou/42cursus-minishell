#include "minishell.h"

int main(void)
{
    char *input;

    while (1)
    {
        input = readline("minishell$ ");
        if (!input)
            break;
        if (*input)
            add_history(input);

        // Parse input

        printf("Input: %s\n", input);

        // execution of the parsed commands

        free(input);
    }
    return 0;
}