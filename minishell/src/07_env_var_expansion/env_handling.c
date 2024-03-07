/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 06:53:11 by zelhajou          #+#    #+#             */
/*   Updated: 2024/03/06 12:39:22 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_variable_start(char *str, int index, int con)
{
	if ((con && str[index] == '$'
			&& str[index + 1]
			&& str[index + 1] != '$'
			&& !ft_isspace(str[index + 1])
			&& (ft_isalnum(str[index + 1])
				|| str[index + 1] == '_'
				|| str[index + 1] == '?'))
		|| (!con && str[index]
			&& str[index] != '$'
			&& !ft_isspace(str[index])
			&& (ft_isalnum(str[index])
				|| str[index] == '_'
				|| str[index] == '?')))
		return (1);
	return (0);
}

void	append_env_var(char *var, t_env *env)
{
	int				b;
	int				c;
	int				d;
	int				o;
	char			*env_var;

	c = sizeof_str(var, '+');
	d = sizeof_str(var, '\0') - c - 1;
	env_var = malloc(c + 1);
	s_strcopy(env_var, var, 0, c);
	o = find_env_var_index(env, env_var);
	free(env_var);
	if (o >= 0)
	{
		b = sizeof_str(env->original_env[o], '\0');
		env_var = malloc(b + d + 1);
		if (!env_var)
			return ;
		s_strcopy(env_var, env->original_env[o], 0, b);
		s_strcopy(env_var + b, var, c + 2, sizeof_str(var, '\0'));
	}
	else
		env_var = str_without_char(var, '+');
	replace_env_var(env_var, env);
	free(env_var);
}

int	find_env_var_index(t_env *env, char *name)
{
	int				a;

	a = 0;
	while (env->parsed_env[a] != 0)
	{
		if (str_cmp(env->parsed_env[a][0], name, NULL))
			return (a);
		a++;
	}
	return (-1);
}
