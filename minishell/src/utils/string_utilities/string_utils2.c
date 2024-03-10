/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beddinao <beddinao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:14:59 by beddinao          #+#    #+#             */
/*   Updated: 2024/03/10 09:52:47 by beddinao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sizeof_str(char *str, char end)
{
	int			a;

	a = 0;
	while (str && str[a] != '\0' && str[a] != end)
		a += 1;
	return (a);
}

int	str_cmp(char *s_1, char *s_2, char *s_3)
{
	int					a;

	a = 0;
	while (s_1[a] && s_2[a] && s_1[a] == s_2[a])
		a += 1;
	if (a == sizeof_str(s_1, '\0')
		&& a == sizeof_str(s_2, '\0'))
		return (1);
	if (s_3)
		return (str_cmp(s_1, s_3, NULL));
	return (0);
}

int	string_to_int(char *str)
{
	int					num;
	int					a;

	num = 0;
	a = 0;
	while (str[a])
	{
		if (str[a] <= '9' && str[a] >= '0')
			num = (num * 10) + (str[a] - 48);
		a++;
	}
	return (num);
}

int	count_strings_in_array(char **arr)
{
	int			a;

	a = 0;
	while (arr[a] != 0)
		a++;
	return (a);
}

void	free_string_array(char **arr)
{
	int				a;

	a = 0;
	while (arr[a] != 0)
	{
		free(arr[a]);
		a += 1;
	}
	free(arr);
}
