/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:00:43 by beddinao          #+#    #+#             */
/*   Updated: 2024/02/27 23:48:36 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin_with_piping(char **_cmd_, int *_fd, t_env *env, int *_piped)
{
	int				status;
	int				_out_fd[2];

	_out_fd[1] = 1;
	if (_piped[0] > 1)
		pipe(_out_fd);
	status = execute_builtin_command_in_child(_cmd_, env, _out_fd);
	if (_piped[0] > 1)
	{
		close(_out_fd[1]);
		_fd[0] = _out_fd[0];
	}
	return (status);
}

int	execute_builtin_with_simple_piping(char **_cmd_, int *_fd, t_env *env, int *_piped)
{
	int				status;
	int				_out_fd[2];

	_out_fd[1] = 1;
	if (_piped[8] && _piped[7])
		_out_fd[1] = _piped[2];
	if (_piped[0] > 1 && (!_piped[8] || !_piped[7]))
		pipe(_out_fd);
	status = execute_builtin_command_in_child(_cmd_, env, _out_fd);
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
	return (status);
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
	int				ex_status;

	status = 0;
	if (_piped[0])
		return (0);
	if (str_cmp(_cmd_[0], "exit", NULL))
	{
		ex_status = 0;
		if (_cmd_[1] && _cmd_[2])
			return (1);
		if (_cmd_[1] && !is_string_numeric(_cmd_[1]))
			ex_status = 255;
		else if (_cmd_[1])
			ex_status = string_to_int(_cmd_[1]);
		free_string_array(_cmd_);
		cleanup_and_exit_shell(env, ex_status);
	}
	else if (!_piped[8])
		status = execute_builtin_with_piping(_cmd_, _fd, env, _piped);
	else
		status = execute_builtin_with_simple_piping(_cmd_, _fd, env, _piped);
	return (status);
}
