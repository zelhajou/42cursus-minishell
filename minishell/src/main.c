/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:00:12 by zelhajou          #+#    #+#             */
/*   Updated: 2024/02/20 16:30:57 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char		*input;
	char		*trimmed_input;
	t_token		*tokens;
	t_ast_node	*ast;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (*input)
			add_history(input);

		trimmed_input = ft_strtrim(input,  " \t\n\v\f\r");
		if (!trimmed_input)
		{
			free(input);
			continue ;
		}
		if (syntax_error_checker(trimmed_input))
		{
			free(input);
			free(trimmed_input);
			continue ;
		}
		tokens = tokenize_input(trimmed_input);
		//display_tokens(tokens);
		free(trimmed_input);
		if (!tokens)
		{
			free(input);
			continue ;
		}
		// TODO: Implement the parser
		ast = parse_tokens(&tokens);
		// TODO: Execute the AST
		// TODO: Free the tokens and the AST
		free_tokens(tokens);
		free_ast(ast);
		free(input);
	}
	return 0;
}
