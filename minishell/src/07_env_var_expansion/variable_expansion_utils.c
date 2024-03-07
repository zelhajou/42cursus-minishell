/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 08:59:59 by beddinao          #+#    #+#             */
/*   Updated: 2024/03/06 12:46:58 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// /// // probably will fail at some point

int	simplified_refactor_thing(char **array, int index, char *str, int in)
{
	int							size;

	if (!str[in] || in > sizeof_str(str, '\0'))
		return (index);
	while (str[in] && str[in] == ' ')
		in++;
	size = sizeof_str(str + in, ' ');
	if (size > sizeof_str(str + in, 34))
		size = sizeof_str(str + in, 34);
	if (size > sizeof_str(str + in, 39))
		size = sizeof_str(str + in, 39);
	if (str[in] == 34)
		size = sizeof_str(str + in + 1, 34) + 2;
	if (str[in] == 39)
		size = sizeof_str(str + in + 1, 39) + 2;
	if ((in + size) > sizeof_str(str, '\0'))
		return (index);
	array[index] = malloc(size + 1);
	if (!array[index])
		return (index);
	s_strcopy(array[index], str, in, in + size);
	return (simplified_refactor_thing(array, index + 1, str, in + size));
}

int	sus_getit_right(char *str, int s_q, int d_q)
{
	int					a;

	a = 0;
	(void)s_q;
	while (str[a])
	{
		if (str[a] == 34 || str[a] == 39
			|| str[a] == '$')
			d_q++;
		a++;
	}
	return (d_q);
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
		res += sus_getit_right(array[a], 0, 0);
		a++;
	}
	return (res);
}
