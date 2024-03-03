/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beddinao <beddinao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 08:59:59 by beddinao          #+#    #+#             */
/*   Updated: 2024/03/03 09:00:02 by beddinao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	simplified_refactor_thing(char **array, int *index, char *str)
{
	int							a;

	a = 0;
	while (str[a] && str[a] == ' ')
		a++;
	while (str[a])
	{
		array[*index] = malloc(sizeof_str(str + a, ' ') + 1);
		s_strcopy(array[*index], str, a, a + sizeof_str(str + a, ' '));
		a += sizeof_str(str + a, ' ') + 1;
		if (a >= sizeof_str(str, '\0'))
			break ;
		while (str[a] && str[a] == ' ')
			a++;
		if (str[a])
			*index += 1;
	}
}

int	is_flawed_str(char *str, int a, int b, int res)
{
	int					si_q;
	int					do_q;

	si_q = 0;
	do_q = 0;
	while (str[a])
	{
		if (str[a] == 34)
			do_q++;
		else if (str[a] == 39)
			si_q++;
		else if (!(si_q % 2) && !(do_q % 2))
		{
			if (str[a] == ' ')
			{
				if (b)
					res++;
				b = 0;
			}
			else
				b = 1;
		}
		a++;
	}
	return (res);
}

int	detected_flaws(char **array)
{
	int			a;
	int			res;

	res = 0;
	a = 0;
	while (array[a])
	{
		res += is_flawed_str(array[a], 0, 0, 0);
		a++;
	}
	return (res);
}
