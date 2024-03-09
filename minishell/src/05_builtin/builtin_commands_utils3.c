/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands_utils3.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:44:36 by zelhajou          #+#    #+#             */
/*   Updated: 2024/03/04 19:31:05 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_print_or_export(char **_cmd_)
{
	int							a;

	a = 1;
	while (_cmd_[a])
	{
		if (_cmd_[a])
			return (1);
		a++;
	}
	return (0);
}

int	export_statment_check(char *_cmd_)
{
	int							a;
	int							b;

	a = sizeof_str(_cmd_, '=');
	if (a > 1 && _cmd_[a - 1] == '+')
		a -= 1;
	if (a)
	{
		b = 0;
		while (b < a)
		{
			if (!b && !ft_isalpha(_cmd_[b]) && _cmd_[b] != '_')
				return (-1);
			else if (b && !ft_isalnum(_cmd_[b]) && _cmd_[b] != '_')
				return (-1);
			b++;
		}
	}
	return (a);
}
