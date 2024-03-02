/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:02:22 by beddinao          #+#    #+#             */
/*   Updated: 2024/02/29 19:02:15 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

///// 	the rules
///
///		_piped[0]: executed pipes index
///
///		_piped[3]: input files_count
///		_piped[4]: output files count
///		_piped[5]: pipes count
///
///		_piped[1]: current input file fd
///		_piped[2]: current output file fd
///
///		_piped[6]: if there is an in file
///		_piped[7]: if there is an out file
///		_piped[8]: if its a redirection/piped execute
///
///		_piped[9]: heredoc status
///		_piped[10]: children count
///		_piped[11]: second heredoc status
/////

int	handle_piped_command_execution(
		t_ast_node *head, int *_piped, t_env *env, int *_fd)
{
	int				status;

	if (head->file_type == EXECUTE_FILE)
	{
		_piped[8] = 0;
		status = prepare_and_execute_command(head->args, _fd, _piped, env);
	}
	if (head->type == TOKEN_REDIR_IN
		|| head->type == TOKEN_REDIR_OUT
		|| head->type == TOKEN_REDIR_APPEND
		|| head->type == TOKEN_REDIR_HEREDOC)
		return (handle_command_redirection(head, _piped, env, _fd));
	if (head->left)
		status = handle_piped_command_execution(head->left, _piped, env, _fd);
	if (head->right)
		status = handle_piped_command_execution(head->right, _piped, env, _fd);
	return (status);
}

int	handle_command_redirection(
		t_ast_node *head, int *_piped, t_env *env, int *_fd)
{
	int				status;

	_piped[11] = 1;
	if (head->right)
		status = open_file_for_redirection(head->right, _piped);
	if (head->left && head->left->file_type == EXECUTE_FILE
		&& _piped[11])
	{
		_piped[8] = 1;
		status = prepare_and_execute_command(
				head->left->args, _fd, _piped, env);
	}
	if (head->left && head->left->type == TOKEN_PIPE
		&& _piped[11])
		status = handle_piped_command_execution(head->left, _piped, env, _fd);
	if (head->left && (head->left->type == TOKEN_REDIR_IN
			|| head->left->type == TOKEN_REDIR_OUT
			|| head->left->type == TOKEN_REDIR_APPEND
			|| head->left->type == TOKEN_REDIR_HEREDOC))
		status = handle_command_redirection(head->left, _piped, env, _fd);
	return (status);
}

int	execute_ast_node(t_ast_node *head, int *_piped, t_env *env)
{
	int					_fd[2];
	int					status;

	if (head->file_type == FILE_READY)
	{
		if (head->type == TOKEN_PIPE)
			status = handle_piped_command_execution(head, _piped, env, _fd);
		if (head->type == TOKEN_REDIR_IN
			|| head->type == TOKEN_REDIR_OUT
			|| head->type == TOKEN_REDIR_APPEND
			|| head->type == TOKEN_REDIR_HEREDOC)
			status = handle_command_redirection(head, _piped, env, _fd);
	}
	if (head->file_type == EXECUTE_FILE)
		status = prepare_and_execute_command(head->args, _fd, _piped, env);
	status = wait_for_children(status, _piped);
	signal(SIGINT, handle_ctrl_c);
	return (status);
}

void	command_execution_manager(t_ast_node *head, t_env *env, int *status)
{
	int				_piped[13];

	initialize_or_reset_pipe_state(_piped, 1);
	count_redirections_and_pipes(head, _piped);
	initialize_or_reset_pipe_state(_piped, 0);
	adjust_ast_nodes_for_execution(head);
	expand_variables_in_ast(head, env);
	if (verify_command_file_permissions(head, env->original_env))
		*status = execute_ast_node(head, _piped, env);
	else
	{
		*status = get_shell_exit_status(errno);
		ft_putstr_fd("\terr: ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
}
