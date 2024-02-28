/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:16:55 by beddinao          #+#    #+#             */
/*   Updated: 2024/02/28 16:26:38 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_allowed_heredoc = 1;
int	stdi_in = 0;

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
	g_allowed_heredoc = 0;
	handle_ctrl_c(a);
}

void	read_and_write(int stdin_fd, int stdout_fd, char *limiter)
{
	char							*buf;

	while (g_allowed_heredoc)
	{
		buf = get_next_line(stdin_fd);
		if (!buf || str_compare(limiter, buf, sizeof_str(buf, '\n')))
		{
			free(buf);
			break ;
		}
		write(stdout_fd, buf, sizeof_str(buf, '\0'));
		free(buf);
	}
}

void	exec_here_doc(char *limiter, int *_piped, int *_fd)
{
	int							_out_fd_[2];

	(void)_fd;
	signal(SIGINT, quite_heredoc);
	pipe(_out_fd_);
	read_and_write(0, _out_fd_[1], limiter);
	close(_out_fd_[1]);
	_piped[9] = g_allowed_heredoc;
	if (_piped[9])
		_piped[1] = _out_fd_[0];
	else
		close_pipe_ends(_out_fd_[0], _out_fd_[1]);
	signal(SIGINT, handle_ctrl_c);
	g_allowed_heredoc = 1;
}
