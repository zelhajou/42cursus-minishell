#include "minishell.h"

void	free_env(s_en *env)
{
	int				a;

	a = 0;
	while (env->env__[a])
	{
		free(env->env__[a][0]);
		free(env->env__[a][1]);
		free(env->env__[a]);
		a += 1;
	}
	free(env->env__);
	free(env);
}

void	terminate(s_en *env)
{
	if (env)
	{
		free_multible(env->__env);
		free_env(env);
	}
	exit(0);
}

void	free_multible(char **arr)
{
	int				a;

	a = 0;
	while (arr[a] != 0)
	{
		free(arr[a]);
		a += 1;
	}
	free(arr);
}

void	close_pipe(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
}

void	ctrl_q_ha(int a)
{
	(void)a;
	rl_forced_update_display();
}
