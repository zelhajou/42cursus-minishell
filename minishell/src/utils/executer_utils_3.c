/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beddinao <beddinao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:16:55 by beddinao          #+#    #+#             */
/*   Updated: 2024/02/27 10:16:57 by beddinao         ###   ########.fr       */
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

void	read_and_write(int stdin_fd, int stdout_fd, char *limiter)
{
	char							*buf;

	while (1)
	{
		buf = get_next_line(stdin_fd);
		if (str_compare(limiter, buf, sizeof_str(buf, '\n')))
			break ;
		write(stdout_fd, buf, sizeof_str(buf, '\0'));
		free(buf);
	}
	free(buf);
}

void	exec_here_doc(char *limiter, int *_piped, int *_fd)
{
	int							_out_fd_[2];

	(void)_fd;
	pipe(_out_fd_);
	read_and_write(0, _out_fd_[1], limiter);
	close(_out_fd_[1]);
	_piped[1] = _out_fd_[0];
}
