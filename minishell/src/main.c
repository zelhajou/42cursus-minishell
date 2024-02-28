/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:00:12 by zelhajou          #+#    #+#             */
/*   Updated: 2024/02/28 00:06:51 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*process_and_tokenize_input(char *input)
{
	char		*trimmed_input;
	t_token		*tokens;

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

void	main_shell_execution_loop(t_env *env)
{
	char		*line;
	int			status;
	t_token		*tokens;
	t_ast_node	*ast;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (check_line(&line))
			continue ;
		add_history(line);
		line = preprocess_builtin_commands_input(line, env);
		tokens = process_and_tokenize_input(line);
		if (!tokens)
			continue ;
		ast = parse_tokens(&tokens);
		command_execution_manager(ast, env, &status);
		update_env_status(env, status, "?=");
		free_ast(ast);
	}
}

int	main(int argc, char **argv, char **original_env)
{
	t_env	*env;

	(void)argv;
	setup_signal_handlers();
	env = malloc(sizeof(t_env));
	if (argc == 1 && isatty(1)
		&& initialize_shell_with_environment(env, original_env))
		main_shell_execution_loop(env);
	cleanup_and_exit_shell(env, 0);
}
