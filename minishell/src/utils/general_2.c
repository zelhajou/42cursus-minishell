/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beddinao <beddinao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:19:45 by beddinao          #+#    #+#             */
/*   Updated: 2024/02/27 10:19:47 by beddinao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_file_error(int err)
{
	if (err == 2)
		return (127);
	else if (err == 13)
		return (126);
	return (err);
}

void	special_signals_handlers(void)
{
	signal(SIGINT, ctrl_c_ha);
	signal(SIGQUIT, SIG_IGN);
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

int	int_size(int num)
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

int	sizeof_arr(char **arr)
{
	int			a;

	a = 0;
	while (arr[a] != 0)
		a++;
	return (a);
}
