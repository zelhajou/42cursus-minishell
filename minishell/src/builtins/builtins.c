#include "minishell.h"

int	echo__(char **_cmd, int *_out_fd)
{
	int				a;
	int				op_n;

	op_n = 0;
	if (_cmd[1] && _cmd[1][1]
		&& _cmd[1][0] == '-' && _cmd[1][1] == 'n')
		op_n = 1;
	a = op_n + 1;
	if (_cmd[a] || sizeof_str(_cmd[a], '\0'))
		while (1)
		{
			ft_putstr_fd(_cmd[a], _out_fd[1]);
			a++;
			if (_cmd[a])
				write(_out_fd[1], " ", 1);
			else
				break ;
		}
	if (!op_n)
		write(_out_fd[1], "\n", 1);
	return (0);
}

int	env_print(char *_cmd, s_en *env, int con, int *_out_fd)
{
	int					a;
	char				*abs_pwd;

	a = 0;
	if (str_cmp(_cmd, "env", NULL))
		while (env->env__[a])
		{
			if (con && !str_cmp(env->env__[a][0], "?", NULL))
				export_print_fd(env->env__[a][0], env->env__[a][1], _out_fd[1]);
			else if (!str_cmp(env->env__[a][1], " ", NULL) && !str_cmp(env->env__[a][0], "?", NULL))
				env_print_fd(env->env__[a][0], env->env__[a][1], _out_fd[1]);
			a++;
		}
	else
	{
		abs_pwd = current_abs_path(100, 5, _out_fd[1]);
		if (abs_pwd)
		{
			ft_putendl_fd(abs_pwd, _out_fd[1]);
			free(abs_pwd);
		}
		else
			return (1);
	}
	return (0);
}

char	**env_modify(char **_cmd, s_en *env, int *_out_fd, int *s)
{
	int				a;
	int				c;

	a = 1;
	*s = 0;
	if (_cmd[a] && str_cmp(_cmd[0], "unset", NULL) && env->env__[0])
		while (_cmd[a])
		{
			c = get_env_index(env, _cmd[a]);
			if (c >= 0)
				env_minus_one(env, c);
			else
				*s = 1;
			a++;
		}
	else if (str_cmp(_cmd[0], "export", NULL))
	{
		_cmd = misstatment_detector(_cmd);
		if (_cmd[a])
			while (_cmd[a])
			{
				if (sizeof_str(_cmd[a], '='))
					env_replace_var(_cmd[a], env);
				else
					*s = 1;
				a++;
			}
		else
			env_print("env", env, 1, _out_fd);
	}
	return (_cmd);
}

int	cd__(char **_cmd, s_en *env, int *_out_fd)
{
	int					a;
	char				*new_path;

	if (_cmd[1] && _cmd[2])
		ft_putendl_fd("\terr: cd(): Not a cd thing", _out_fd[1]);
	else
	{
		if (change_dir(_cmd[1], env) < 0)
			ft_putendl_fd("\terr: chdir(): Only (relative/absolute) EXISTING paths", _out_fd[1]);
		else
		{
			a = get_env_index(env, "PWD");
			if (a >= 0)
				env_minus_one(env, a);
			new_path = current_abs_path(100, 5, _out_fd[1]);
			if (new_path)
			{
				update_pwd_env(new_path, env, a);
				free(new_path);
			}
			return (0);
		}
	}
	return (1);
}
