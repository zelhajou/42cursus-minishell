/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:00:12 by zelhajou          #+#    #+#             */
/*   Updated: 2024/02/24 23:07:26 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token		*syntax_check_and_tokenize(char *input)
{
	char					*trimmed_input;
	t_token					*tokens;

	trimmed_input = ft_strtrim(input, " \t\n\v\f\r");
	free(input);
	if (!trimmed_input)
		return (NULL);
	if (syntax_error_checker(trimmed_input))
	{
		free(trimmed_input);
		return (NULL);
	}
	tokens = tokenize_input(trimmed_input);
	free(trimmed_input);
	return (tokens);
}

void	shell_loop(s_en *env)
{
	char					*line;
	int					status;
	t_token					*tokens;
	t_ast_node				*ast;

	while (1)
	{
		line = readline("\t> ");
		if (!line)
			break;
		if (check_line(&line))
			continue;
		add_history(line);
		line = ex_statment_misdefinition(line);
		tokens = syntax_check_and_tokenize(line);
		if (!tokens)
			continue;
		ast = parse_tokens(&tokens);
		//generate_ast_diagram(ast);
		general_execution(ast, env, &status);
		adapt_status_env(env, status, "?=");
		free_ast(ast);
	}
}

void	ex_signals_handling(void)
{
	signal(SIGINT, ctrl_c_ha);
	signal(SIGQUIT, SIG_IGN);
}

int main(int argc, char **argv, char **__env)
{
	s_en					*env;

	(void)argv;
	ex_signals_handling();
	env = malloc(sizeof(s_en));
	if (argc == 1 && isatty(1)
		&& __shell_init(env, __env))
		shell_loop(env);
	terminate(env);
}
