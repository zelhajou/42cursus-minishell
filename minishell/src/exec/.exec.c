#include "../../includes/minishell.h"

int	is_builtin(char *_cmd)
{
	char		*tmp_cmd;
	int		status;

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

void	_standards_init(t_ast_node *head, int *_piped)
{
	_piped[2] = 1;
	if (head->file_type != X_F)
		_piped[2] = 0;
	if (_piped[5] > 0)
		_piped[1] = 1;
	else if (!_piped[4])
		_piped[1] = 0;
}

void	_standards_out(t_ast_node *head, int *_piped)
{
	if (head->file_type == X_F)
		_piped[5] -= 1;
	if (_piped[1])
		_piped[0] = 1;
}

int	exec_one(char **_cmd_, int *_fd, char **env, int *_piped)
{
	pid_t				pid;
	int				fd_[2];

	pipe(fd_);
	pid = fork();
	if (pid < 0)
		return (0);
	if (!pid)
	{
		if (_piped[0])
			dup2(_fd[0], 0);
		if (_piped[1])
		{
			if (_piped[5] > 0)
				dup2(fd_[1], 1);
			else if (_piped[4])
				dup2(_fd[1], 1);
		}
		close_pipe(fd_[0], fd_[1]);
		execve(_cmd_[0], _cmd_, env);
		exit(EXIT_FAILURE);
	}
	close(fd_[1]);
	_fd[0] = fd_[0];
	return (1);
}

int	builtins_child(char **_cmd_, int *_fd, s_en *env, int *_piped)
{
	int					fd_[2];
	int					status;
	pid_t					pid;

	pipe(fd_);
	pid = fork();
	if (!pid)
	{
		if (_piped[0])
			dup2(_fd[0], 0);
		if (_piped[1])
		{
			if (_piped[5] > 0)
				dup2(fd_[1], 1);
			else
				dup2(_fd[1], 1);
		}
		close_pipe(fd_[0], fd_[1]);
		if (str_cmp(_cmd_[0], "echo", NULL))
			status = echo__(_cmd_);
		else if (str_cmp(_cmd_[0], "pwd", "env"))
			status = env_print(_cmd_[0], env, 0);
		else if (str_cmp(_cmd_[0], "export", "unset"))
			status = env_modify(_cmd_, env);
		else if (str_cmp(_cmd_[0], "cd", NULL))
			status = cd__(_cmd_, env);
		exit(status);
	}
	close(fd_[1]);
	_fd[0] = fd_[0];
	return (1);
}

int	exec_built_in(char **_cmd_, int *_fd, s_en *env, int *_piped)
{
	int					status;

	status = 1;
	if (str_cmp(_cmd_[0], "exit", NULL))
	{
		free_multible(_cmd_);
		terminate(env);
	}
	else
		status = builtins_child(_cmd_, _fd, env, _piped);
	return (status);
}

char	**merge_it(char **f_args, char **_cmd_)
{
	int				a;
	char				**new_args;

	if (!f_args)
		return (NULL);
	a = 1;
	while (_cmd_[a])
		a++;
	new_args = malloc((a + 1) * sizeof(char *));
	a = 0;
	new_args[a] = strcopy(f_args[a]);
	while (_cmd_[++a])
		new_args[a] = strcopy(_cmd_[a]);
	new_args[a] = 0;
	free_multible(f_args);
	for (int i = 0; new_args[i]; i++)
		printf("->> arg[%i]: .%s.\n", i, new_args[i]);
	printf("---------------------------------------------\n");
	return (new_args);
}

int	exec_command(char **_cmd_, int *_fd, int *_piped, s_en *env)
{
	char				**cmd_args;
	char				**f_args;
	int				status;

	f_args = generate_cmd_arr(_cmd_[0], env->__env, 0);
	cmd_args = merge_it(f_args, _cmd_);
	printf("-- executing: %s, with _pipes[%i, %i], and %i\n",   cmd_args[0], _piped[0], _piped[1], _piped[5]);
	if (!cmd_args)
		return (0);
	if (is_builtin(cmd_args[0]))
		status = exec_built_in(cmd_args, _fd, env, _piped);
	else
		status = exec_one(cmd_args, _fd, env->__env, _piped);
	free_multible(cmd_args);
	return (status);
}

int	execute(t_ast_node *head, s_en *env, int *_fd, int *_piped)
{
	int				status;
	
	status = 1;
	_standards_init(head, _piped);
	if (_piped[2])
		status = exec_command(head->args, _fd, _piped, env);
	if (status && head->left)
		status = execute(head->left, env, _fd, _piped);
	if (status && head->right)
		status = execute(head->right, env, _fd, _piped);
	_standards_out(head, _piped);
	if (!_piped[1])
		close(_fd[0]);
	return (status);
}

void	_open_next_input_(t_ast_node *head, int _in_index, int *_piped, int *_fd)
{
	if (head->file_type == R_F)
	{
		if (_piped[6] == _in_index)
		{
			_fd[0] = open(head->args[0], O_RDONLY);
			_piped[0] = 1;
			printf("got input:   .%s.\n", head->args[0]);
		}
		_piped[6] += 1;
	}
	if (_piped[3] && head->left)
		_open_next_input_(head->left, _in_index, _piped, _fd);
	if (_piped[3] && head->right)
		_open_next_input_(head->right, _in_index, _piped, _fd);
}

void	_open_next_output_(t_ast_node *head, int _out_index, int *_piped, int *_fd)
{
	if (head->file_type == W_F || head->file_type == W_FA)
	{
		if (_piped[6] == _out_index)
		{
			if (head->file_type == W_F)
				_fd[1] = open(head->args[0], O_WRONLY| O_CREAT| O_TRUNC, 0666);
			else
				_fd[1] = open(head->args[0], O_WRONLY| O_CREAT| O_APPEND, 0666);
			_piped[1] = 1;
			printf("got output:  .%s.\n", head->args[0]);
		}
		_piped[6] += 1;
	}
	if (_piped[4] && head->right)
		_open_next_output_(head->right, _out_index, _piped, _fd);
	if (_piped[4] && head->left)
		_open_next_output_(head->left, _out_index, _piped, _fd);
}

int	__files_permission(t_ast_node *head, char **env)
{
	int				status;
	char				*path_;

	status = 1;
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

int	execution_loop(t_ast_node *head, int *_piped, s_en *env)
{
	int				_in_index;
	int				_out_index;
	int				status;
	int				_fd[2];

	_fd[0] = 0;
	_in_index = 0;
	status = 1;
	while (status && (!_in_index || _in_index < _piped[3]))
	{
		_out_index = 0;
		_piped[6] = _piped[0] = 0;
		_open_next_input_(head, _in_index++, _piped, _fd);
		while (status && (!_out_index || _out_index < _piped[4]))
		{
			_piped[6] = _piped[1] = 0;
			_open_next_output_(head, _out_index++, _piped, _fd);
			status = execute(head, env, _fd, _piped);
		}
	}
	if (status)
		wait(&status);
	return (WEXITSTATUS(status));
}

void	___confirm_it(t_ast_node *head, int *_piped, int times)
{
	if (!times)
		printf("%s\n---> the numbers: %i inputs, %i outputs and %i pipes\n",
			"---------------------------------------------", _piped[3], _piped[4], _piped[5]);
	if (head->file_type == X_F)
		printf("-> executable: %s\n",  head->args ? head->args[0] : "null");
	else if (head->file_type == W_F || head->file_type == W_FA)
		printf("-> output file: %s\n", head->args ? head->args[0] : "null");
	else if (head->file_type == R_F)
		printf("-> input file: %s\n",  head->args ? head->args[0] : "null");
	if (head->left)
		___confirm_it(head->left, _piped, times + 1);
	if (head->right)
		___confirm_it(head->right, _piped, times + 1);
}

//	\e[1;1H\e[2J

void	general_execution(t_ast_node *head, s_en *env, int *status)
{
	int				_piped[7];

	*status = 1;
	_piped[3] = 0;
	_piped[4] = 0;
	_piped[5] = 0;
	__redirection_count(head, _piped);
	__adapt_nodes(head);
	___confirm_it(head, _piped, 0);
	if (__files_permission(head, env->__env))
	{
		printf("\n[files checks passed]\n");
		*status = execution_loop(head, _piped, env);
	}
	else
	{
		*status = errno;
		printf("\terr: %s\n", strerror(errno));
	}
}
