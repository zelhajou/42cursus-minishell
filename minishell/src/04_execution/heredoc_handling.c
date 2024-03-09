/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:16:55 by beddinao          #+#    #+#             */
/*   Updated: 2024/02/29 16:20:16 by beddinao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_compare(char *s_1, char *s_2, int max)
{
	int								a;

	a = 0;
	while (a < max && *s_1 && *s_2
		&& s_1[a] == s_2[a])
		a++;
	if (sizeof_str(s_1, '\0') == a
		&& a == max)
		return (1);
	return (0);
}

void	quite_heredoc(int a)
{
	(void)a;
	write(1, "\n", 1);
	exit(0);
}

int	is_there_any_quotes(char *s)
{
	int						a;

	a = 0;
	while (s && s[a])
	{
		if (s[a] == 34 || s[a] == 39)
			return (0);
		a++;
	}
	return (1);
}

void	read_and_write(
	int std_out, char *limiter, t_env *env, int is_expandable)
{
	char							*buf;
	int								f_arr[3];

	limiter = remove_quotes_from_str(limiter, 0, 0, 0);
	while (1)
	{
		buf = readline(">> ");
		if (!buf || str_compare(limiter, buf, sizeof_str(buf, '\n')))
		{
			free(buf);
			break ;
		}
		if (is_expandable)
		{
			buf[sizeof_str(buf, '\n')] = '\0';
			ft_memset(f_arr, 0, 3 * sizeof(int));
			buf = recursively_expand_variables(buf, env, 0, f_arr);
			ft_memset(f_arr, 0, 3 * sizeof(int));
			buf = recursively_expand_variables(buf, env, 1, f_arr);
		}
		write(std_out, buf, sizeof_str(buf, '\0'));
		write(std_out, "\n", 1);
		free(buf);
	}
	free(limiter);
}

int	exec_here_doc(char *limiter, int *_piped, t_env *env)
{
	int							_out_fd_[2];
	pid_t						pid;
	int							status;

	pipe(_out_fd_);
	pid = fork();
	signal(SIGINT, SIG_IGN);
	if (!pid)
	{
		signal(SIGINT, quite_heredoc);
		close(_out_fd_[0]);
		read_and_write(_out_fd_[1], limiter, env,
			is_there_any_quotes(limiter));
		exit(1);
	}
	waitpid(pid, &status, 0);
	close(_out_fd_[1]);
	_piped[1] = _out_fd_[0];
	_piped[9] = (WEXITSTATUS(status)) - 1;
	if (_piped[9] < 0)
		_piped[9] += 2;
	_piped[11] = status;
	return (_piped[9]);
}
