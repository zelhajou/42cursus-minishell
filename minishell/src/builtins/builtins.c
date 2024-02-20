#include "../../includes/exec.h"

int	echo__(char **_cmd)
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
			printf("%s", _cmd[a]);
			a++;
			if (_cmd[a])
				printf(" ");
			else
				break ;
		}
	if (!op_n)
		printf("\n");
	return (0);
}

int	env_print(char *_cmd, s_en *env, int con)
{
	int					a;
	char				*abs_pwd;

	a = 0;
	if (str_cmp(_cmd, "env", NULL))
		while (env->env__[a])
		{
			if (con && !str_cmp(env->env__[a][0], "?", NULL))
				printf("declare -x %s=%c%s%c\n", env->env__[a][0], '"', env->env__[a][1], '"');
			else if (!str_cmp(env->env__[a][1], " ", NULL) && !str_cmp(env->env__[a][0], "?", NULL))
				printf("%s : %s\n",env->env__[a][0], env->env__[a][1]);
			a++;
		}
	else
	{
		abs_pwd = current_abs_path(100, 5);
		if (abs_pwd)
		{
			printf("%s\n", abs_pwd);
			free(abs_pwd);
		}
		else
			return (256);
	}
	return (0);
}

int	env_modify(char **_cmd, s_en *env)
{
	int				a;
	int				c;
	int				s;

	a = 1;
	s = 0;
	if (_cmd[a] && str_cmp(_cmd[0], "unset", NULL) && env->env__[0])
		while (_cmd[a])
		{
			c = get_env_index(env, _cmd[a]);
			if (c >= 0)
				env_minus_one(env, c);
			else
				s = 256;
			a++;
		}
	else if (str_cmp(_cmd[0], "export", NULL))
	{
		if (_cmd[a])
			while (_cmd[a])
			{
				if (sizeof_str(_cmd[a], '='))
					env_replace_var(_cmd[a], env);
				else
					s = 256;
				a++;
			}
		else
			env_print("env", env, 1);
	}
	return (s);
}

int	cd__(char **_cmd, s_en *env)
{
	int					a;
	char				*new_path;

	if (_cmd[1] && _cmd[2])
		printf("\terr: cd(): Not a cd thing\n");
	else
	{
		if (change_dir(_cmd[1], env) < 0)
			printf("\terr: chdir(): Only (relative/absolute) EXISTING paths\n");
		else
		{
			a = get_env_index(env, "PWD");
			if (a >= 0)
				env_minus_one(env, a);
			new_path = current_abs_path(100, 5);
			if (new_path)
			{
				update_pwd_env(new_path, env, a);
				free(new_path);
			}
			return (0);
		}
	}
	return (256);
}
