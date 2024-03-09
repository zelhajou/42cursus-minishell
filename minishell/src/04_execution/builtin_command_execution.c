/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_command_execution.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:00:43 by beddinao          #+#    #+#             */
/*   Updated: 2024/03/09 18:19:35 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	simple_child_for_builtins(char **_cmd_, int *_fd, t_env *env, int *_piped)
{
	pid_t					pid;
	int						fd_[2];
	int						_out_fd_[2];
	int						status;

	(pipe(fd_), pid = fork());
	if (!pid)
	{
		if (_piped[0] && _piped[0] <= _piped[5])
			dup2(_fd[0], 0);
		if (_piped[0] > 1)
			dup2(fd_[1], 1);
		else
			close(_fd[0]);
		close_pipe_ends(fd_[0], fd_[1]);
		dup2(1, _out_fd_[1]);
		status = execute_builtin_command_in_child(_cmd_, env, _out_fd_, _piped);
		exit(WEXITSTATUS(status));
	}
	close(fd_[1]);
	if (_piped[0] && _piped[0] <= _piped[5])
		close(_fd[0]);
	if (_piped[0] > 1)
		_fd[0] = fd_[0];
	else
		close(fd_[0]);
	return (1);
}

void	exec_builtin_and_exit(
	char **_cmd_, t_env *env, int *_out_fd, int *_piped)
{
	int				status;

	status = execute_builtin_command_in_child(
			_cmd_, env, _out_fd, _piped);
	exit(WEXITSTATUS(status));
}

int	execute_child_with_redirections(
		char **_cmd_, int *_fd, t_env *env, int *_piped)
{
	pid_t			pid;
	int				_out_fd[2];

	_out_fd[1] = 1;
	if (_piped[8] && _piped[7])
		_out_fd[1] = _piped[2];
	if (_piped[0] > 1 && (!_piped[8] || !_piped[7]))
		pipe(_out_fd);
	pid = fork();
	if (!pid)
		exec_builtin_and_exit(_cmd_, env, _out_fd, _piped);
	if (_piped[8] && _piped[7])
	{
		close(_out_fd[1]);
		_piped[7] = 0;
	}
	if (!_piped[6] && !_piped[7])
		_piped[8] = 0;
	if (_piped[0] > 1 && (!_piped[8] || !_piped[7]))
	{
		close(_out_fd[1]);
		_fd[0] = _out_fd[0];
	}
	if (_piped[0] && _piped[0] <= _piped[5])
		close(_fd[0]);
	return (1);
}

int	is_string_numeric(char *s_1)
{
	int				a;

	a = 0;
	while (s_1[a])
	{
		if (!ft_isdigit(s_1[a]))
			return (0);
		a++;
	}
	return (1);
}

int	manage_builtin_execution(char **_cmd_, int *_fd, t_env *env, int *_piped)
{
	int				status;

	status = 0;
	_piped[10] += 1;
	if (_piped[0])
	{
		if (!_piped[8])
			status = simple_child_for_builtins(_cmd_, _fd, env, _piped);
		else
			status = execute_child_with_redirections(_cmd_, _fd, env, _piped);
		free_string_array(_cmd_);
	}
	else
		status = manage_single_builtin_execution(_cmd_, _fd, env, _piped);
	return (status);
}
