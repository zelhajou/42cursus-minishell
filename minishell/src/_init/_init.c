#include "../../includes/minishell.h"

char	**setup_old_env(char **env)
{
	int				a;
	int				b;
	char				**new_old;

	a = 0;
	b = 0;
	while (env[a])
		a++;
	new_old = malloc((a + 1) * sizeof(char **));
	while (b < a)
	{
		new_old[b] = strcopy(env[b]);
		b++;
	}
	new_old[b] = 0;
	return (new_old);
}

int	__setup_env(s_en *env, char **__env)
{
	int				a;
	int				b;
	int				c;

	a = 0;
	if (!env)
		return (0);
	env->__env = setup_old_env(__env);
	while (__env[a])
		a++;
	env->env__ = malloc((a + 1) * sizeof(char ***));
	if (!env->env__)
		return (0);
	b = 0;
	while (b < a)
	{
		c = sizeof_str(__env[b], '=');
		env->env__[b] = malloc(2 * sizeof(char **));
		env->env__[b][0] = malloc(c * sizeof(char *));
		env->env__[b][1] = malloc((sizeof_str(__env[b], '\0') - c) * sizeof(char *));
		s_strcopy(env->env__[b][0], __env[b], 0, c);
		s_strcopy(env->env__[b][1], __env[b], c + 1, sizeof_str(__env[b], '\0'));
		b++;
	}
	env->env__[b] = 0;
	return (1);
}

int	__shell_init(s_en *env, char **__env)
{
	int					__index;
	int					status;
	int					a;

	status = __setup_env(env, __env);
	a = get_env_index(env, "SHLVL");
	__index = 0;
	if (a >= 0)
		__index = string_to_int(env->env__[a][1]);
	adapt_status_env(env, __index + 1, "SHLVL=");
	//>
	a = get_env_index(env, "SHELL");
	if (a >= 0)
		env_minus_one(env, a);
	env_replace_var("SHELL=minishell", env);
	return (status);
}
