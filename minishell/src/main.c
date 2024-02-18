/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:00:12 by zelhajou          #+#    #+#             */
/*   Updated: 2024/02/17 20:15:58 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
    char	*input;
	t_token	*tokens;
	//t_ast_node *ast;

	while (1)
    {
        input = readline("minishell$ ");
        if (!input)
            break;
        if (*input)
            add_history(input);
		// Tokenize input
		if (!syntax_error_checker(ft_strtrim(input,  " \t\n\v\f\r")))
		{
			tokens = tokenize_input(ft_strtrim(input,  " \t\n\v\f\r"));
			if (!tokens)
			{
				free(input);
				continue;
			}
		}
		else
		{
			free(input);
			continue;
		}
		// Parse input
		// ast = parse_tokens(tokens);
		// display the tokens
		display_tokens(tokens);
        // execution of the parsed commands
        free(input);
    }
    return 0;
}
