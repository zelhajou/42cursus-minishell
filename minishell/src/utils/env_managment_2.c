/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_managment_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:53:44 by beddinao          #+#    #+#             */
/*   Updated: 2024/02/29 16:22:35 by beddinao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_env_var(char *var, t_env *env)
{
	int				c;
	int				o;
	char			*env_var;

	c = sizeof_str(var, '=');
	env_var = malloc(c + 1);
	s_strcopy(env_var, var, 0, c);
	o = find_env_var_index(env, env_var);
	if (o >= 0)
		remove_env_entry(env, o);
	free(env_var);
	if (c > 0 && c < sizeof_str(var, '\0') - 1)
		add_env_entry(env, var, c, 1);
	else if (var[c] == '=')
		add_env_entry(env, var, c, 0);
	else if (c == sizeof_str(var, '\0'))
		add_env_entry(env, var, c, -1);
}

void	update_env_status(t_env *env, int status, char *start)
{
	char					*var;
	int						a;

	a = count_digits_in_int(status) + sizeof_str(start, '\0') + 1;
	var = malloc(a);
	s_strcopy(var, start, 0, sizeof_str(start, '\0'));
	var[--a] = '\0';
	if (!status)
		var[--a] = '0';
	while (status)
	{
		var[--a] = (status % 10) + 48;
		status /= 10;
	}
	replace_env_var(var, env);
	free(var);
}

int	is_space(char *line)
{
	int				a;

	a = 0;
	while (line[a] == ' ' || line[a] == '\t'
		|| line[a] == '\n')
		a += 1;
	if (line[a] == '\0')
		return (1);
	return (0);
}

int	check_line(char **line)
{
	if (*line[0] == '\0' || str_cmp(*line, "\n", NULL) || is_space(*line))
	{
		free(*line);
		return (1);
	}
	return (0);
}

char	*str_without_char(char *str, char del)
{
	int				a;
	int				b;
	char			*new_str;

	a = 0;
	b = 0;
	new_str = malloc(sizeof_str(str, '\0') + 1);
	while (str[a])
	{
		if (str[a] != del)
			new_str[b++] = str[a];
		a++;
	}
	new_str[b] = '\0';
	return (new_str);
}
