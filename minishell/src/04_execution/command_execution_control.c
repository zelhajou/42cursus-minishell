/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution_control.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beddinao <beddinao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:11:08 by beddinao          #+#    #+#             */
/*   Updated: 2024/03/10 14:13:13 by beddinao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_or_reset_pipe_state(int *_piped, int f)
{
	int			a;

	a = 0;
	_piped[0] = _piped[5];
	if (f)
		while (a < 12)
			_piped[a++] = 0;
	else if (_piped[5])
		_piped[0] += 1;
	_piped[11] = 1;
}

int	switch_fds_identifier(
		int *_piped, int index, int index_2, int con)
{
	if (con)
	{
		if (_piped[index])
			close(_piped[index_2]);
		_piped[index] = 1;
	}
	else
	{
		ft_putendl_fd("err: file not found", 2);
		_piped[6] = 0;
	}
	return (1);
}

int	open_file_for_redirection(
		t_ast_node *head, int *_piped, t_env *env, int status)
{
	int			mode;

	if (head->file_type == READ_FILE)
	{
		switch_fds_identifier(_piped, 6, 1, 1);
		_piped[1] = open(head->args[0], O_RDONLY);
		if (_piped[1] < 0)
			status = switch_fds_identifier(_piped, 0, 0, 0);
	}
	else if (head->file_type == READ_FROM_APPEND)
	{
		switch_fds_identifier(_piped, 6, 1, 1);
		status = exec_here_doc(head->args[0], _piped, env);
		signal(SIGINT, handle_ctrl_c);
	}
	else
	{
		switch_fds_identifier(_piped, 7, 2, 1);
		mode = O_TRUNC;
		if (head->file_type == WRITE_FILE_APPEND)
			mode = O_APPEND;
		_piped[2] = open(head->args[0], O_WRONLY | O_CREAT | mode, 0666);
	}
	return (status);
}

int	check_if_command_is_builtin(char *_cmd)
{
	char		*tmp_cmd;
	int			status;

	status = 0;
	tmp_cmd = malloc(sizeof_str(_cmd, ' ') + 1);
	if (!tmp_cmd)
		return (0);
	s_strcopy(tmp_cmd, _cmd, 0, sizeof_str(_cmd, ' '));
	if (str_cmp(tmp_cmd, "echo", "cd")
		|| str_cmp(tmp_cmd, "pwd", "export")
		|| str_cmp(tmp_cmd, "unset", "env")
		|| str_cmp(tmp_cmd, "exit", NULL))
		status = 1;
	free(tmp_cmd);
	return (status);
}

int	execute_builtin_command_in_child(
		char **_cmd_, t_env *env, int *_out_fd, int *_piped)
{
	int			status;

	status = 0;
	(void)_piped;
	if (str_cmp(_cmd_[0], "echo", NULL))
		status = echo_cmd(_cmd_, _out_fd);
	else if (str_cmp(_cmd_[0], "pwd", "env"))
		status = env_or_pwd_cmd(_cmd_[0], env, 0, _out_fd);
	else if (str_cmp(_cmd_[0], "export", "unset"))
		_cmd_ = unset_or_export_cmd(_cmd_, env, _out_fd, &status);
	else if (str_cmp(_cmd_[0], "cd", NULL))
		status = cd_cmd(_cmd_, env, _out_fd);
	else if (str_cmp(_cmd_[0], "exit", NULL))
		__exit(_cmd_);
	free_string_array(_cmd_);
	return (status);
}
