/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beddinao <beddinao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:02:22 by beddinao          #+#    #+#             */
/*   Updated: 2024/02/27 14:53:36 by beddinao         ###   ########.fr       */
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
/////

int	execute_pipe(t_ast_node *head, int *_piped, t_en *env, int *_fd)
{
	int				status;

	if (head->file_type == X_F)
	{
		_piped[8] = 0;
		status = exec_command(head->args, _fd, _piped, env);
	}
	if (head->type == TOKEN_REDIR_IN
		|| head->type == TOKEN_REDIR_OUT
		|| head->type == TOKEN_REDIR_APPEND
		|| head->type == TOKEN_REDIR_HEREDOC)
		return (execute_redirection(head, _piped, env, _fd));
	if (head->left)
		status = execute_pipe(head->left, _piped, env, _fd);
	if (head->right)
		status = execute_pipe(head->right, _piped, env, _fd);
	return (status);
}

int	execute_redirection(t_ast_node *head, int *_piped, t_en *env, int *_fd)
{
	int				status;

	if (head->right)
		open_file(head->right, _piped);
	if (head->left && head->left->file_type == X_F)
	{
		_piped[8] = 1;
		status = exec_command(head->left->args, _fd, _piped, env);
	}
	if (head->left && head->left->type == TOKEN_PIPE)
		status = execute_pipe(head->left, _piped, env, _fd);
	if (head->left && (head->left->type == TOKEN_REDIR_IN
			|| head->left->type == TOKEN_REDIR_OUT
			|| head->left->type == TOKEN_REDIR_APPEND
			|| head->left->type == TOKEN_REDIR_HEREDOC))
		status = execute_redirection(head->left, _piped, env, _fd);
	return (status);
}

int	execution_circle(t_ast_node *head, int *_piped, t_en *env)
{
	int					_fd[2];
	int					status;

	if (head->file_type == F_R)
	{
		if (head->type == TOKEN_PIPE)
			status = execute_pipe(head, _piped, env, _fd);
		if (head->type == TOKEN_REDIR_IN
			|| head->type == TOKEN_REDIR_OUT
			|| head->type == TOKEN_REDIR_APPEND
			|| head->type == TOKEN_REDIR_HEREDOC)
			status = execute_redirection(head, _piped, env, _fd);
	}
	if (head->file_type == X_F)
		status = exec_command(head->args, _fd, _piped, env);
	return (status);
}

void	general_execution(t_ast_node *head, t_en *env, int *status)
{
	int				_piped[10];

	_piped_init(_piped, 1);
	__redirection_count(head, _piped);
	_piped_init(_piped, 0);
	__adapt_nodes(head);
	_expand_it(head, env);
	if (__files_permission(head, env->__env))
		*status = execution_circle(head, _piped, env);
	else
	{
		*status = b_file_error(errno);
		printf("\terr: %s\n", strerror(errno));
	}
}
