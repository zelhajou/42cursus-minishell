/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:11:08 by beddinao          #+#    #+#             */
/*   Updated: 2024/02/27 23:48:36 by zelhajou         ###   ########.fr       */
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
}

void	open_file_for_redirection(t_ast_node *head, int *_piped)
{
	int			mode;

	_piped[9] = 1;
	if (head->file_type == R_F)
	{
		_piped[6] = 1;
		_piped[1] = open(head->args[0], O_RDONLY);
	}
	else if (head->file_type == R_FA)
	{
		_piped[6] = 1;
		exec_here_doc(head->args[0], _piped, NULL);
	}
	else
	{
		_piped[7] = 1;
		mode = O_TRUNC;
		if (head->file_type == W_FA)
			mode = O_APPEND;
		_piped[2] = open(head->args[0], O_WRONLY | O_CREAT | mode, 0666);
	}
}

int	check_if_command_is_builtin(char *_cmd)
{
	char		*tmp_cmd;
	int			status;

	status = 0;
	tmp_cmd = malloc(sizeof_str(_cmd, ' ') + 1);
	s_strcopy(tmp_cmd, _cmd, 0, sizeof_str(_cmd, ' '));
	if (str_cmp(tmp_cmd, "echo", "cd")
		|| str_cmp(tmp_cmd, "pwd", "export")
		|| str_cmp(tmp_cmd, "unset", "env")
		|| str_cmp(tmp_cmd, "exit", NULL))
		status = 1;
	free(tmp_cmd);
	return (status);
}

int	execute_builtin_command_in_child(char **_cmd_, t_env *env, int *_out_fd)
{
	int			status;

	status = 0;
	if (str_cmp(_cmd_[0], "echo", NULL))
		status = echo__(_cmd_, _out_fd);
	else if (str_cmp(_cmd_[0], "pwd", "env"))
		status = env_print(_cmd_[0], env, 0, _out_fd);
	else if (str_cmp(_cmd_[0], "export", "unset"))
		_cmd_ = env_modify(_cmd_, env, _out_fd, &status);
	else if (str_cmp(_cmd_[0], "cd", NULL))
		status = cd__(_cmd_, env, _out_fd);
	free_string_array(_cmd_);
	return (status);
}
