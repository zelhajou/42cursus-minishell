void	exec_one(char **_cmd, int *_fd, char **env, int *_piped)
{
	pid_t						pid;
	int							fd_[2];

	pipe(fd_);
	pid = fork();
	if (pid == 0)
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
		execve(_cmd[0], _cmd, env);
		perror("execution failure");
	}
	close_fd(_fd[0], fd_[1]);
	_fd[0] = fd_[0];
}

int	exec_command(char *_cmd_, int *_fd, int *_piped, char **env)
{
	char				**cmd_args;

	/*printf("\nCMD: %s;  piped: [ %i,  %i ];	w: %i;\n",
	 * _cmd_, _piped[0], _piped[1], _piped[5]);*/
	cmd_args = generate_cmd_arr(_cmd_, env, 0);
	if (!cmd_args)
		return (0);
	exec_one(cmd_args, _fd, env, _piped);
	return (1);
}

int	execute(s_tree *head, char **env, int *_fd, int *_piped)
{
	int					status;

	_standards_init(head, _fd, _piped);
	// exec
	status = 1;
	if (_piped[2])
		status = exec_command(head->val, _fd, _piped, env);
	//>
	if (status)
	{
		if (head->right)
			status = execute(head->right, env, _fd, _piped);
		if (head->left)
			status = execute(head->left, env, _fd, _piped);
	}
	_standards_out(head, _fd, _piped);
	return (status);
}

int	general_execution(s_tree *head, char **env)
{
	int					_in_index;
	int					_out_index;
	int					_fd[2];
	int					_piped[8];
	int					status;

	_fd[0] = 0;
	status = 1;
	_piped[3] = 0;
	_piped[4] = 0;
	_piped[5] = 0;
	__in_redirection_count(head, _piped);
	__out_redirection_count(head, _piped);
	__pipes_count(head, _piped);
	__adapt_nodes_types(head);
	_in_index = 0;
	/*printf("the numbers :\t[%i] inputs, [%i] outputs, [%i] pipes\n\n",
		_piped[3], _piped[4], _piped[5]);*/
	while (status && (!_in_index || _in_index < _piped[3]))
	{
		_out_index = 0;
		_piped[6] = _piped[0] = 0;
		open_next_input(head, _in_index++, _piped, _fd);
		while (status && (!_out_index || _out_index < _piped[4]))
		{
			_piped[6] = _piped[1] = 0;
			open_next_output(head, _out_index++, _piped, _fd);
			status = execute(head, env, _fd, _piped);
		}
	}
	wait(NULL);
	return (status);
}
