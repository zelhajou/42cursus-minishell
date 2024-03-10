/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_managment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beddinao <beddinao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:08:31 by beddinao          #+#    #+#             */
/*   Updated: 2024/03/10 09:48:58 by beddinao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env_exclude_index(char **env, int a, int a_2, int d)
{
	char				**new_thing;
	int					b;
	int					c;

	b = 0;
	c = 0;
	new_thing = malloc((a + a_2) * sizeof(char **));
	if (!new_thing)
		return (NULL);
	while (b < a)
	{
		if (b != d)
			new_thing[c++] = strcopy(env[b]);
		b++;
	}
	if (d >= 0)
		new_thing[c] = 0;
	free_string_array(env);
	return (new_thing);
}

char	***duplicate_env_structure(t_env *env, int a, int a_2, int d)
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
			if (!new_thing[c])
				return (NULL);
			new_thing[c][0] = strcopy(env->parsed_env[b][0]);
			new_thing[c][1] = strcopy(env->parsed_env[b][1]);
			c++;
		}
		b++;
	}
	if (d >= 0)
		new_thing[c] = 0;
	if (a_2 != 'F')
		free_environment_variables(env->parsed_env);
	return (new_thing);
}

void	remove_env_entry(t_env *env, int c)
{
	int				a;

	a = 0;
	while (env->parsed_env[a] != 0)
		a++;
	if (a > 0)
	{
		env->parsed_env = duplicate_env_structure(env, a, 0, c);
		env->original_env = copy_env_exclude_index(env->original_env, a, 0, c);
	}
}

void	update_env_value_at_index(t_env *env, char *cmd, int a, int con)
{
	int				b;
	int				c;

	b = sizeof_str(cmd, '=');
	c = sizeof_str(cmd, '\0') - b;
	if (con > 0)
	{
		env->parsed_env[a][1] = malloc(c + 1);
		if (!env->parsed_env[a][1])
			return ;
		s_strcopy(env->parsed_env[a][1], cmd, b + 1, b + c);
	}
	else
	{
		env->parsed_env[a][1] = malloc(3);
		if (!env->parsed_env[a][1])
			return ;
		if (!con)
			env->parsed_env[a][1][0] = '\0';
		else
			s_strcopy(env->parsed_env[a][1], "F1", 0, 2);
	}
}

void	add_env_entry(t_env *env, char *cmd, int b, int con)
{
	int				a;
	int				c;

	a = 0;
	c = 2;
	if (con)
		c = sizeof_str(cmd, '\0') - b;
	while (env->parsed_env[a] != 0)
		a++;
	env->parsed_env = duplicate_env_structure(env, a, 2, -1);
	env->original_env = copy_env_exclude_index(env->original_env, a, 2, -1);
	env->original_env[a] = malloc(b + c + 1);
	env->parsed_env[a] = malloc(2 * sizeof(char *));
	env->parsed_env[a][0] = malloc(b + 1);
	if (!env->parsed_env[a] || !env->parsed_env[a][0] || !env->original_env[a])
		return ;
	s_strcopy(env->parsed_env[a][0], cmd, 0, b);
	if (con > 0)
		s_strcopy(env->original_env[a], cmd, 0, sizeof_str(cmd, '\0'));
	else
		s_strcopy(env->original_env[a], "  ", 0, 1);
	update_env_value_at_index(env, cmd, a, con);
	env->original_env[a + 1] = 0;
	env->parsed_env[a + 1] = 0;
}
