/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specific_task_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:15:13 by beddinao          #+#    #+#             */
/*   Updated: 2024/02/28 15:36:28 by zelhajou         ###   ########.fr       */
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
	char				*env_var;

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

void	copy_str_without_quotes(char *new_str, char *old_str, int size)
{
	int					a;
	int					b;

	a = 0;
	b = 0;
	while (old_str && a < size)
	{
		if (old_str[b] != 34 && old_str[b] != 39)
			new_str[a++] = old_str[b];
		b++;
	}
	new_str[a] = '\0';
}

char	*remove_quotes_from_str(char *str)
{
	char				*new_str;
	int					b;
	int					a;
	int					size;

	a = 0;
	size = 0;
	b = sizeof_str(str, '\0');
	while (str && a < b)
	{
		if (str[a] != 34 && str[a] != 39)
			size++;
		a++;
	}
	new_str = malloc(size + 1);
	copy_str_without_quotes(new_str, str, size);
	free(str);
	return (new_str);
}
