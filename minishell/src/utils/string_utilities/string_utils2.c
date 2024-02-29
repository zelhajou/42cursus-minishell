/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:14:59 by beddinao          #+#    #+#             */
/*   Updated: 2024/02/29 18:56:33 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
