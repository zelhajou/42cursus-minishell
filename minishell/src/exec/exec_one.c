/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beddinao <beddinao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:01:18 by beddinao          #+#    #+#             */
/*   Updated: 2024/02/27 10:55:31 by beddinao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//// /// /// / execution part

int	exec_one(char **_cmd_, int *_fd, char **env, int *_piped)
{
	pid_t				pid;
	int					status;
	int					fd_[2];

	pipe(fd_);
	pid = fork();
	if (!pid)
	{
		if (_piped[0] && _piped[0] <= _piped[5])
			dup2(_fd[0], 0);
		if (_piped[0] > 1)
			dup2(fd_[1], 1);
		else
			close(_fd[0]);
		close_pipe(fd_[0], fd_[1]);
		execve(_cmd_[0], _cmd_, env);
		exit(EXIT_FAILURE);
	}
	close_pipe(fd_[1], _fd[0]);
	if (_piped[0] > 1)
		_fd[0] = fd_[0];
	else
		close(fd_[0]);
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

int	exec_simple_one(char **_cmd_, int *_fd, char **env, int *_piped)
{
	pid_t				pid;
	int					fd_[2];
	int					status;

	pipe(fd_);
	pid = fork();
	if (!pid)
	{
		child_fds_managment(_piped, _fd, fd_);
		execve(_cmd_[0], _cmd_, env);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
	parent_fds_managment(_piped, _fd, fd_);
	free_multible(_cmd_);
	return (WEXITSTATUS(status));
}

int	exec_command(char **_cmd_, int *_fd, int *_piped, t_en *env)
{
	char				**cmd_args;
	char				**f_args;
	int					status;

	f_args = generate_cmd_arr(_cmd_[0], env->__env, 0);
	cmd_args = merge_it(f_args, _cmd_);
	if (!cmd_args)
		return (0);
	if (is_builtin(cmd_args[0]))
		status = exec_built_ins(cmd_args, _fd, env, _piped);
	else if (!_piped[8])
	{
		status = exec_one(cmd_args, _fd, env->__env, _piped);
		free_multible(cmd_args);
	}
	else
		status = exec_simple_one(cmd_args, _fd, env->__env, _piped);
	if (_piped[0] > 1)
		_piped[0] -= 1;
	return (status);
}
