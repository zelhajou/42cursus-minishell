/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:55:35 by beddinao          #+#    #+#             */
/*   Updated: 2024/03/06 14:39:23 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**duplicate_environment_variables(char **env)
{
	int				a;
	int				b;
	char			**new_old;

	a = 0;
	b = 0;
	while (env[a])
		a++;
	new_old = malloc((a + 1) * sizeof(char **));
	if (!new_old)
		return (NULL);
	while (b < a)
	{
		new_old[b] = strcopy(env[b]);
		b++;
	}
	new_old[b] = 0;
	return (new_old);
}

int	initialize_shell_environment_structure(
		t_env *env, char **original_env, int a)
{
	int				b;
	int				c;

	env->original_env = duplicate_environment_variables(original_env);
	while (original_env[a])
		a++;
	env->parsed_env = malloc((a + 1) * sizeof(char ***));
	if (!env->parsed_env)
		return (0);
	b = -1;
	while (++b < a)
	{
		c = sizeof_str(original_env[b], '=');
		env->parsed_env[b] = malloc(2 * sizeof(char **));
		env->parsed_env[b][0] = malloc(c * sizeof(char *));
		env->parsed_env[b][1] = malloc(
				(sizeof_str(original_env[b], '\0') - c) * sizeof(char *));
		if (!env->parsed_env[b] || !env->parsed_env[b][0]
			|| !env->parsed_env[b][1])
			return (0);
		s_strcopy(env->parsed_env[b][0], original_env[b], 0, c);
		s_strcopy(env->parsed_env[b][1], original_env[b],
			c + 1, sizeof_str(original_env[b], '\0'));
	}
	return (env->parsed_env[b] = 0, 1);
}

int	initialize_shell_with_environment(t_env *env, char **original_env)
{
	int					__index;
	int					status;
	int					a;

	if (!env)
		return (0);
	status = initialize_shell_environment_structure(env, original_env, 0);
	a = find_env_var_index(env, "SHLVL");
	__index = 0;
	if (a >= 0)
		__index = string_to_int(env->parsed_env[a][1]);
	update_env_status(env, __index + 1, "SHLVL=");
	a = find_env_var_index(env, "SHELL");
	if (a >= 0)
		remove_env_entry(env, a);
	replace_env_var("SHELL=minishell", env);
	replace_env_var("?=0", env);
	return (status);
}
