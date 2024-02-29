/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:19:45 by beddinao          #+#    #+#             */
/*   Updated: 2024/02/29 06:55:10 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_shell_exit_status(int err)
{
	if (err == 2)
		return (127);
	else if (err == 13)
		return (126);
	return (err);
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

int	count_digits_in_int(int num)
{
	int			a;

	a = 0;
	if (!num)
		return (1);
	while (num)
	{
		num /= 10;
		a++;
	}
	return (a);
}

int	count_strings_in_array(char **arr)
{
	int			a;

	a = 0;
	while (arr[a] != 0)
		a++;
	return (a);
}
