#include "minishell.h"

int	__files_permission(t_ast_node *head, char **env)
{
	int				status;
	char				*path_;

	status = 1;
	path_ = NULL;
	if (head->args && !is_builtin(head->args[0])
		&& (head->file_type == R_F || head->file_type == X_F))
	{
		if (head->file_type == R_F)
			path_ = get_file_path(head->args[0], env, "PWD", R_OK);
		else if (head->file_type == X_F)
			path_ = get_file_path(head->args[0], env, "PATH", X_OK);
		if (!path_)
			status = 0;
		else
			free(path_);
	}
	if (status && head->left)
		status = __files_permission(head->left, env);
	if (status && head->right)
		status = __files_permission(head->right, env);
	return (status);
}

void	__adapt_nodes(t_ast_node *head)
{
	if (head->type != TOKEN_WORD)
	{
		head->file_type = F_R;
		if (head->type == TOKEN_REDIR_OUT && head->right)
			head->right->file_type = W_F;
		if (head->type == TOKEN_REDIR_APPEND && head->right)
			head->right->file_type = W_FA;
		if ((head->type == TOKEN_REDIR_IN
			|| head->type == TOKEN_REDIR_HEREDOC) && head->right)
			head->right->file_type = R_F;
		if (head->type == TOKEN_PIPE)
		{
			if (head->right)
				head->right->file_type = X_F;
			if (head->left)
				head->left->file_type = X_F;
		}
	}
	if (!head->file_type)
		head->file_type = X_F;
	if (head->left)
		__adapt_nodes(head->left);
	if (head->right)
		__adapt_nodes(head->right);
}

void	__redirection_count(t_ast_node *head, int *_piped)
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
		__redirection_count(head->left, _piped);
	if (head->right)
		__redirection_count(head->right, _piped);
}
