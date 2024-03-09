/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:00:12 by zelhajou          #+#    #+#             */
/*   Updated: 2024/03/09 18:18:20 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int fd[2];

	fd[0] = dup(0);
	fd[1] = dup(1);
	while (1)
	{
		ast = NULL;
		tokens = NULL;
		line = NULL;
		status = 0;
		line = readline(" > ");
		if (!line)
			break ;
		if (check_line(&line))
			continue ;
		add_history(line);
		tokens = process_and_tokenize_input(line);
		if (!tokens)
			status = 258;
		else
		{
			ast = parse_tokens(&tokens);
			command_execution_manager(ast, env, &status);
			free_ast(ast);
			dup2(fd[0], 0);
			dup2(fd[1], 1);
		}
		update_env_status(env, status, "?=");
	}
	close(fd[0]);
	close(fd[1]);
}

int	main(int argc, char **argv, char **original_env)
{
	t_env	*env;

	(void)argv;
	setup_signal_handlers();
	env = malloc(sizeof(t_env));
	printf("--|%i|--\n", getpid());
	if (!isatty(1) || !isatty(0))
		return (free(env), 0);
	if (argc == 1 && initialize_shell_with_environment(env, original_env))
	{
		main_shell_execution_loop(env);
		cleanup_and_exit_shell(env, 0);
	}
	return (0);
}
