/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beddinao <beddinao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:55:35 by beddinao          #+#    #+#             */
/*   Updated: 2024/02/27 10:47:31 by beddinao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**setup_old_env(char **env)
{
	int				a;
	int				b;
	char			**new_old;

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

int	__setup_env(t_en *env, char **__env, int a)
{
	int				b;
	int				c;

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
		env->env__[b][1] = malloc(
				(sizeof_str(__env[b], '\0') - c) * sizeof(char *));
		s_strcopy(env->env__[b][0], __env[b], 0, c);
		s_strcopy(env->env__[b][1], __env[b],
			c + 1, sizeof_str(__env[b], '\0'));
		b++;
	}
	env->env__[b] = 0;
	return (1);
}

int	__shell_init(t_en *env, char **__env)
{
	int					__index;
	int					status;
	int					a;

	if (!env)
		return (0);
	status = __setup_env(env, __env, 0);
	a = get_env_index(env, "SHLVL");
	__index = 0;
	if (a >= 0)
		__index = string_to_int(env->env__[a][1]);
	adapt_status_env(env, __index + 1, "SHLVL=");
	a = get_env_index(env, "SHELL");
	if (a >= 0)
		env_minus_one(env, a);
	env_replace_var("SHELL=minishell", env);
	return (status);
}
