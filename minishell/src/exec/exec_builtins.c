#include "../../includes/minishell.h"

int	exec_builtins(char **_cmd_, int *_fd, s_en *env, int *_piped)
{
	int				status;
	int				_out_fd[2];

	_out_fd[1] = 1;
	if (_piped[0] > 1)
		pipe(_out_fd);
	//>
	status = builtins_child(_cmd_, env, _out_fd);
	//<
	if (_piped[0] > 1)
	{
		close(_out_fd[1]);
		_fd[0] = _out_fd[0];
	}
	return (status);
}

int	exec_simple_builtins(char **_cmd_, int *_fd, s_en *env, int *_piped)
{
	int				status;
	int				_out_fd[2];

	_out_fd[1] = 1;
	if (_piped[8] && _piped[7])
		_out_fd[1] = _piped[2];
	if (_piped[0] > 1 && (!_piped[8] || !_piped[7]))
		pipe(_out_fd);
	//>
	status = builtins_child(_cmd_, env, _out_fd);
	//<
	if (_piped[8] && _piped[7])
	{
		close(_out_fd[1]);
		_piped[7] = 0;
	}
	if (!_piped[6] && !_piped[7])
		_piped[8] = 0;
	if (_piped[0] > 1 && (!_piped[8] || !_piped[7]))
	{
		close(_out_fd[1]);
		_fd[0] = _out_fd[0];
	}
	return (status);
}

int	exec_built_ins(char **_cmd_, int *_fd, s_en *env, int *_piped)
{
	int				status;

	if (str_cmp(_cmd_[0], "exit", NULL))
	{
		free_multible(_cmd_);
		terminate(env);
	}
	else if (!_piped[8])
		status = exec_builtins(_cmd_, _fd, env, _piped);
	else
		status = exec_simple_builtins(_cmd_, _fd, env, _piped);
	return (status);
}
