#include "minishell.h"

int main(void)
{
    char *input;
	t_token *tokens;


	while (1)
    {
        input = readline("minishell$ ");
		printf("Input: %s\n", input);
        if (!input)
            break;
        if (*input)
            add_history(input);
		// Tokenize input
		tokens = tokenize_input(input);
		if (!tokens)
		{
			free(input);
			continue;
		}
		// display the tokens
		display_tokens(tokens);

        // Parse input


        // execution of the parsed commands
        free(input);
    }
    return 0;
}