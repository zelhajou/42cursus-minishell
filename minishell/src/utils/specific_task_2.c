/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specific_task_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beddinao <beddinao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:15:13 by beddinao          #+#    #+#             */
/*   Updated: 2024/02/27 10:15:14 by beddinao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_env_index(t_en *env, char *name)
{
	int				a;

	a = 0;
	while (env->env__[a] != 0)
	{
		if (str_cmp(env->env__[a][0], name, NULL))
			return (a);
		a++;
	}
	return (-1);
}

char	*adapt_quoted_str(char *str)
{
	char				*new_str;
	int					a;
	int					b;

	a = 0;
	b = sizeof_str(str, '\0');
	if (str && str[0] == '"' && str[b - 1] == '"')
	{
		a += 1;
		b -= 1;
	}
	new_str = malloc((b - a) + 1);
	s_strcopy(new_str, str, a, b);
	free(str);
	return (new_str);
}
