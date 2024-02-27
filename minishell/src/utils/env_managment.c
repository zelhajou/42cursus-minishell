/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_managment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beddinao <beddinao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:08:31 by beddinao          #+#    #+#             */
/*   Updated: 2024/02/27 10:10:08 by beddinao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**old_new_copy(char **env, int a, int a_2, int d)
{
	char				**new_thing;
	int					b;
	int					c;

	b = 0;
	c = 0;
	new_thing = malloc((a + a_2) * sizeof(char **));
	while (b < a)
	{
		if (b != d)
			new_thing[c++] = strcopy(env[b]);
		b++;
	}
	if (d >= 0)
		new_thing[c] = 0;
	free_multible(env);
	return (new_thing);
}

char	***env_copy(t_en *env, int a, int a_2, int d)
{
	int				b;
	int				c;
	char			***new_thing;

	b = 0;
	c = 0;
	new_thing = malloc((a + a_2) * sizeof(char ***));
	while (b < a)
	{
		if (b != d)
		{
			new_thing[c] = malloc(2 * sizeof(char **));
			new_thing[c][0] = strcopy(env->env__[b][0]);
			new_thing[c][1] = strcopy(env->env__[b][1]);
			c++;
		}
		free(env->env__[b][0]);
		free(env->env__[b][1]);
		free(env->env__[b]);
		b++;
	}
	if (d >= 0)
		new_thing[c] = 0;
	free(env->env__);
	return (new_thing);
}

void	env_minus_one(t_en *env, int c)
{
	int				a;

	a = 0;
	while (env->env__[a] != 0)
		a++;
	if (a > 0)
	{
		env->env__ = env_copy(env, a, 0, c);
		env->__env = old_new_copy(env->__env, a, 0, c);
	}
}

void	env_plus_value(t_en *env, char *cmd, int a, int con)
{
	int				b;
	int				c;

	b = sizeof_str(cmd, '=');
	c = sizeof_str(cmd, '\0') - b;
	if (con > 0)
	{
		env->env__[a][1] = malloc(c + 1);
		s_strcopy(env->env__[a][1], cmd, b + 1, b + c);
	}
	else
	{
		env->env__[a][1] = malloc(3);
		if (!con)
			env->env__[a][1][0] = '\0';
		else
			s_strcopy(env->env__[a][1], "F1", 0, 2);
	}
}

void	env_plus_one(t_en *env, char *cmd, int b, int con)
{
	int				a;
	int				c;

	a = 0;
	c = 2;
	if (con)
		c = sizeof_str(cmd, '\0') - b;
	while (env->env__[a] != 0)
		a++;
	env->env__ = env_copy(env, a, 2, -1);
	env->__env = old_new_copy(env->__env, a, 2, -1);
	env->__env[a] = malloc(b + c + 1);
	env->env__[a] = malloc(2 * sizeof(char *));
	env->env__[a][0] = malloc(b + 1);
	s_strcopy(env->env__[a][0], cmd, 0, b);
	if (con > 0)
		s_strcopy(env->__env[a], cmd, 0, sizeof_str(cmd, '\0'));
	else
		s_strcopy(env->__env[a], "  ", 0, 1);
	env_plus_value(env, cmd, a, con);
	env->__env[a + 1] = 0;
	env->env__[a + 1] = 0;
}
