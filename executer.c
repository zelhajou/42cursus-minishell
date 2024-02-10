#include "m.h"

void	close_fd(int fd_1, int fd_2)
{
	close(fd_1);
	close(fd_2);
}

int	sizeof_str(char *str, char end)
{
	int			a;

	a = 0;
	while (str[a] != '\0' && str[a] != end)
		a += 1;
	return (a);
}
int		str_cmp(char *s_1, char *s_2, char *s_3)
{
	int					a;

	a = 0;
	while (s_1[a] && s_2[a] && s_1[a] == s_2[a])
		a += 1;
	if (a == sizeof_str(s_1, '\0')
		&& a == sizeof_str(s_2, '\0'))
		return (1);
	if (s_3)
		return (str_cmp(s_1, s_3, NULL));
	return (0);
}

int	get_string_accurance(char **haystack, char *needle, int n_length)
{
	int		a;
	int		b;

	a = 0;
	while (haystack[a] != 0)
	{
		if (haystack[a][0] == needle[0])
		{
			b = 0;
			while (haystack[a][b]
				&& haystack[a][b] == needle[b])
			{
				if (b == n_length - 1)
					return (a);
				b++;
			}
		}
		a++;
	}
	return (-1);
}

int	check_strs_existence(char **argv, int argc)
{
	int		a;

	a = 1;
	while (a < argc - 1)
	{
		if (!sizeof_str(argv[a], '\0'))
			return (0);
		a++;
	}
	return (1);
}

int	check_path_access(char *path, int mode)
{
	if (access(path, mode) < 0)
		return (0);
	return (1);
}

void	increment_path_index(char *env_var, int *indx_s, int *a)
{
	if (indx_s[3])
	{
		indx_s[1] += 1;
		*a = indx_s[1];
		while (env_var[indx_s[1]] != '\0'
			&& env_var[indx_s[1]] != ':')
			indx_s[1] += 1;
	}
	else
		*a = indx_s[1];
}

char	*get_var_subpaths(char *env_var, char *file, int *indx_s)
{
	char		*tmp_path;
	int			a;
	int			b;
	int			file_size;

	increment_path_index(env_var, indx_s, &a);
	file_size = sizeof_str(file, ' ');
	tmp_path = malloc((indx_s[1] - a) + file_size + 1);
	if (!tmp_path)
		return (NULL);
	b = 0;
	while (b < ((indx_s[1] - a) + file_size + 1))
	{
		if (indx_s[3] && (b < indx_s[1] - a))
			tmp_path[b] = env_var[a + b];
		else if (indx_s[3]
			&& env_var[indx_s[1] - 1] != '/'
			&& (b == indx_s[1] - a))
			tmp_path[b] = '/';
		else
			tmp_path[b] = file[b - (indx_s[1] - a) - indx_s[3]];
		b++;
	}
	tmp_path[b] = '\0';
	return (tmp_path);
}

char	*get_file_path(char *file, char **envp, char *env_var, int mode)
{
	char		*tmp_path;
	int			indx_s[4];

	indx_s[3] = 0;
	indx_s[1] = sizeof_str(env_var, '\0');
	indx_s[0] = get_string_accurance(envp, env_var, indx_s[1]);
	if (indx_s[0] < 0)
		return (NULL);
	indx_s[2] = sizeof_str(envp[indx_s[0]], '\0');
	while (envp[indx_s[0]][indx_s[1]])
	{
		tmp_path = get_var_subpaths(envp[indx_s[0]], file, indx_s);
		if (!tmp_path)
			return (NULL);
		if (check_path_access(tmp_path, mode))
			return (tmp_path);
		free(tmp_path);
		if (!indx_s[3])
			indx_s[3] = 1;
	}
	return (NULL);
}

int	get_strs_count(char *str, char del)
{
	int			a;
	int			b;
	int			res;

	a = 0;
	b = 1;
	res = 0;
	while (str && str[a])
	{
		if (str[a] != del)
		{
			if (b)
				res += 1;
			b = 0;
		}
		else
			b = 1;
		a += 1;
	}
	return (res);
}

char	*get_next_substr(char *str, char del, int *index)
{
	char		*sub;
	int			size;
	int			a;

	while (str[index[0]] && str[index[0]] == del)
		index[0] += 1;
	size = sizeof_str(str + index[0], del);
	sub = malloc(size + 1);
	if (!sub)
		return (NULL);
	a = 0;
	while (str[index[0]]
		&& str[index[0]] != del)
	{
		sub[a] = str[index[0]];
		a += 1;
		index[0] += 1;
	}
	sub[a] = '\0';
	index[0] += 1;
	return (sub);
}

char	**generate_cmd_arr(char *cmd, char **envp, int c)
{
	char		**cmd_arr;
	char		*cmd_holder;
	int			i[2];

	i[1] = get_strs_count(cmd, ' ');
	cmd_arr = malloc((i[1] + 1) * sizeof(char *));
	if (!cmd_arr)
		return (NULL);
	i[0] = 0;
	while (c < i[1])
	{
		cmd_holder = get_next_substr(cmd, ' ', i);
		if (!c)
		{
			cmd_arr[c] = get_file_path(cmd_holder, envp, "PATH", X_OK);
			free(cmd_holder);
		}
		else
			cmd_arr[c] = cmd_holder;
		if (!cmd_arr[c])
			return (NULL);
		c += 1;
	}
	cmd_arr[c] = NULL;
	return (cmd_arr);
}

void	exec_one(char **cmd, int *_fd, char **env, int *piped)
{
	pid_t					pid;
	int						fd_[2];

	pipe(fd_);
	pid = fork();
	if (pid == 0)
	{
		if (piped[0])
			dup2(_fd[0], 0);
		if (piped[1])
		{
			if (piped[2])
				dup2(_fd[1], 1);
			else
				dup2(fd_[1], 1);
		}
		//close_fd(fd_[0], fd_[1]);
		execve(cmd[0], cmd, env);
		perror("execution error");
	}
	close_fd(_fd[0], fd_[1]);
	_fd[0] = fd_[0];
}

int	is_red(char *str)
{
	if (str_cmp(str, "|", NULL) || str_cmp(str, ">", ">>")
			|| str_cmp(str, "<", "<<"))
		return (1);
	return (0);
}

int	exec_command(char	*cmd, int *_fd, int *piped, char **env)
{
	char			**cmd_args;
	
	cmd_args = generate_cmd_arr(cmd, env, 0);
	printf("----> [%s] (%i, %i)\n",     cmd_args[0], piped[0], piped[1]);
	if (!cmd_args)
		return (0);
	exec_one(cmd_args, _fd, env, piped);
	return (1);
}

void	setup_indx_s(char *str, int *_a)
{
	if (str_cmp(str, "|", NULL))
		_a[1] = _a[1] < 0 ? 1 : _a[1] ? 0 : -1;
	else if (str_cmp(str, "<", "<<"))
		_a[0] = _a[0] < 0 ? 1 : _a[0] ? 0 : -1;
	else if (str_cmp(str, ">", ">>"))
		_a[2] = _a[2] < 0 ? 1 : _a[2] ? 0 : -1;
}

void	reset_indx_s(char *str, int *_a)
{
	if (str_cmp(str, "|", NULL))
		_a[1] = !_a[1] ? -1 : 1;
	else if (str_cmp(str, "<", "<<"))
		_a[0] = !_a[0] ? -1 : 1;
	else if (str_cmp(str, ">", ">>"))
		_a[2] = !_a[2] ? -1 : 1;	
}

int	get_output(s_tree *head)
{
	int					fd;

	while (head)
	{
		if (str_cmp(head->val, ">", ">>")
				&& head->left)
		{
			if (str_cmp(head->val, ">>", NULL))
				fd = open(head->left->val, O_WRONLY | O_CREAT | O_APPEND, 0666);
			else
				fd = open(head->left->val, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			break ;
		}
		head = head->prev;
	}
	return (fd);
}

int	setup_standards(s_tree *head, int *_fd, int *_a, char **env)
{
	int					piped[3];

	piped[0] = 0;
	piped[1] = 0;
	piped[2] = 0;
	if (_a[0] > 0)
	{
		_fd[0] = open(head->val, O_RDONLY);
		return (1);
	}
	if (!_a[0] || !_a[1])
		piped[0] = 1;
	if (_a[1] > 0 || _a[2] > 0)
	{
		if (head->prev && _a[2] > 0
				&& _a[0] < 1 && _a[1] < 1)
		{
			_fd[1] = get_output(head->prev);
			piped[2] = 1;
		}
		piped[1] = 1;
	}
	if (_a[2])
		return (exec_command(head->val, _fd, piped, env));
	return (1);
}

int		execute(s_tree *head, char **env, int *_fd, int *_a)
{
	int					status;

	status = 1;
	if (head->prev)
		setup_indx_s(head->prev->val, _a);
	// exec
	if (!is_red(head->val))
		status = setup_standards(head, _fd, _a, env);
	//>
	if (status)
	{
		if (head->right)
			status = execute(head->right, env, _fd, _a);
		if (head->left)
			status = execute(head->left, env, _fd, _a);
	}
	reset_indx_s(head->val, _a);
	return (status);
}

int	general_execution(s_tree *head, char **env)
{
	int					_fd[2];
	int					_a[3];
	int					status;

	_a[0] = -1;
	_a[1] = -1;
	_a[2] = -1;
	_fd[0] = 0;
	status = execute(head, env, _fd, _a);
	wait(NULL);
	return (status);
}
