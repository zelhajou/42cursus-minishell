#include "minishell.h"

void	_piped_init(int *_piped, int f)
{
	int			a;

	a = 0;
	_piped[0] = _piped[5];
	if (f)
		while (a < 10)
			_piped[a++] = 0;
	else if (_piped[5])
		_piped[0] += 1;
}

void	open_file(t_ast_node *head, int *_piped)
{
	int			mode;

	if (head->file_type == R_F)
	{
		_piped[6] = 1;
		_piped[1] = open(head->args[0], O_RDONLY);
	}
	else
	{
		_piped[7] = 1;
		mode = O_TRUNC;
		if (head->file_type == W_FA)
			mode = O_APPEND;
		_piped[2] = open(head->args[0], O_WRONLY| O_CREAT| mode, 0666);
	}
}

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

int	builtins_child(char **_cmd_, s_en *env, int *_out_fd)
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
	free_multible(_cmd_);
	return (status);
}
