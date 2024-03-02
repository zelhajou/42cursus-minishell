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

void	read_and_write(int std_out, char *limiter)
{
	char							*buf;

	while (1)
	{
		buf = readline(" >> ");
		if (!buf || str_compare(limiter, buf, sizeof_str(buf, '\n')))
		{
			free(buf);
			break ;
		}
		write(std_out, buf, sizeof_str(buf, '\0'));
		write(std_out, "\n", 1);
		free(buf);
	}
}

int	exec_here_doc(char *limiter, int *_piped, int *_fd)
{
	int							_out_fd_[2];
	pid_t						pid;
	int							status;

	(void)_fd;
	pipe(_out_fd_);
	pid = fork();
	if (!pid)
	{
		signal(SIGINT, quite_heredoc);
		signal(SIGQUIT, SIG_IGN);
		close(_out_fd_[0]);
		read_and_write(_out_fd_[1], limiter);
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
