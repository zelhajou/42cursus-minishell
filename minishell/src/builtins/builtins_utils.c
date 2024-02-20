#include "../../includes/exec.h"

//// // // cd

void	update_pwd_env(char *new_, s_en *env, int c)
{
	char				**exp_pwd;
	int				a;
	int				b;

	a = 0;
	b = 4;
	exp_pwd = malloc(3 * sizeof(char *));
	exp_pwd[0] = strcopy("export");
	exp_pwd[1] = malloc(sizeof_str(new_, '\0') + 5);
	s_strcopy(exp_pwd[1], "PWD=", 0, 4);
	while (new_[a])
		exp_pwd[1][b++] = new_[a++];
	exp_pwd[1][b] = '\0';
	exp_pwd[2] = 0;
	env_modify(exp_pwd, env);
	free_multible(exp_pwd);
}

int		change_dir(char *path, s_en *env)
{
	int					status;
	int					a;

	if (!path || !sizeof_str(path, '\0'))
	{
		a = get_env_index(env, "HOME");
		if (a >= 0)
			status = chdir(env->env__[a][1]);
		else
			status = -1;
	}
	else
		status = chdir(path);
	return (status);
}

// /// // PWD

char	*current_abs_path(int size, int tries)
{
	char				*buffer;

	buffer = malloc(size);
	if (!buffer)
		return (NULL);
	if (!getcwd(buffer, size))
	{
		free(buffer);
		if (tries < 10)
			return (current_abs_path(size + 50, tries + 1));
		else
		{
			printf("\tgetcwd() failure: you are lost\n");
			return (NULL);
		}
	}
	return (buffer);
}
