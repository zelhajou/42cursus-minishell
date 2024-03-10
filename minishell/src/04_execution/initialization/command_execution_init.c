/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution_init.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beddinao <beddinao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:56:04 by beddinao          #+#    #+#             */
/*   Updated: 2024/03/10 13:59:33 by beddinao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sus_dir_check(char *path_, char *file, int *status)
{
	struct stat		s;

	if (file && str_cmp(file, ".", NULL))
		*status = 2;
	else if (str_cmp(file, "..", NULL)
		|| str_cmp(file, ",", ""))
	{
		*status = 1;
		errno = 2;
	}
	else if (!stat(path_, &s)
		&& s.st_mode & S_IFDIR)
	{
		*status = 2;
		ft_putstr_fd("   err: this \'", 2);
		ft_putstr_fd(path_, 2);
		ft_putendl_fd("\' Is a directory", 2);
		errno = 13;
	}
}

int	specify_what_error_stuff(char *file, int _status)
{
	if (_status == 1)
	{
		_status = get_shell_exit_status(errno);
		ft_putstr_fd("   err: \'", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd("\' ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (_status);
	}
	else if (_status)
	{
		ft_putstr_fd("   minishell(\'", 2);
		ft_putstr_fd(file, 2);
		ft_putendl_fd("\'): go play somewhere elsz", 2);
	}
	return (_status);
}

int	verify_command_file_permissions(t_ast_node *head, char **env)
{
	int				status;
	char			*path_;

	status = 0;
	if (head->args
		&& !check_if_command_is_builtin(head->args[0])
		&& head->file_type == READ_FILE)
	{
		path_ = fetch_file_path(head->args[0], env, "PWD", R_OK);
		if (!path_)
			status = 0;
		else
		{
			sus_dir_check(path_, head->args[0], &status);
			free(path_);
		}
		status = specify_what_error_stuff(head->args[0], status);
	}
	if (!status && head->left)
		status = verify_command_file_permissions(head->left, env);
	if (!status && head->right)
		status = verify_command_file_permissions(head->right, env);
	return (status);
}

void	adjust_ast_nodes_for_execution(t_ast_node *head)
{
	if (head->type != TOKEN_WORD)
	{
		head->file_type = FILE_READY;
		if (head->type == TOKEN_REDIR_OUT && head->right)
			head->right->file_type = WRITE_FILE;
		if (head->type == TOKEN_REDIR_APPEND && head->right)
			head->right->file_type = WRITE_FILE_APPEND;
		if (head->type == TOKEN_REDIR_IN && head->right)
			head->right->file_type = READ_FILE;
		if (head->type == TOKEN_REDIR_HEREDOC && head->right)
			head->right->file_type = READ_FROM_APPEND;
		if (head->type == TOKEN_PIPE)
		{
			if (head->right)
				head->right->file_type = EXECUTE_FILE;
			if (head->left)
				head->left->file_type = EXECUTE_FILE;
		}
	}
	if (!head->file_type)
		head->file_type = EXECUTE_FILE;
	if (head->left)
		adjust_ast_nodes_for_execution(head->left);
	if (head->right)
		adjust_ast_nodes_for_execution(head->right);
}

void	count_redirections_and_pipes(t_ast_node *head, int *_piped)
{
	head->file_type = 0;
	if (head->type == TOKEN_REDIR_OUT
		|| head->type == TOKEN_REDIR_APPEND)
		_piped[4] += 1;
	else if (head->type == TOKEN_REDIR_IN
		|| head->type == TOKEN_REDIR_HEREDOC)
		_piped[3] += 1;
	else if (head->type == TOKEN_PIPE)
		_piped[5] += 1;
	if (head->left)
		count_redirections_and_pipes(head->left, _piped);
	if (head->right)
		count_redirections_and_pipes(head->right, _piped);
}
