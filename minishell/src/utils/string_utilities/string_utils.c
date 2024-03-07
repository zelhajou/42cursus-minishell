/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 06:51:24 by zelhajou          #+#    #+#             */
/*   Updated: 2024/03/07 11:31:41 by beddinao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes_from_str(char *str, int si_q_c, int do_q_c, int a)
{
	char				*new_str;
	int					b;

	b = 0;
	new_str = malloc(sizeof_str(str, '\0') + 1);
	if (!new_str)
		return (NULL);
	while (str[a])
	{
		if (str[a] == 34 && !(si_q_c % 2))
			do_q_c++;
		else if (str[a] == 39 && !(do_q_c % 2))
			si_q_c++;
		if ((str[a] != 34 || si_q_c % 2)
			&& (str[a] != 39 || do_q_c % 2))
			new_str[b++] = str[a];
		a++;
	}//      " /'\ /' "    " '\ "
	new_str[b] = '\0';
	return (free(str), new_str);
}

char	*strcopy(char *src)
{
	int					a;
	int					b;
	char				*dest;

	b = 0;
	while (src[b])
		b += 1;
	dest = malloc(b + 1);
	if (!dest)
		return (NULL);
	a = 0;
	while (a < b)
	{
		dest[a] = src[a];
		a += 1;
	}
	dest[a] = '\0';
	return (dest);
}

void	s_strcopy(char *s_1, char *s_2, int st, int en)
{
	int				a;

	a = 0;
	while (st < en)
		s_1[a++] = s_2[st++];
	s_1[a] = '\0';
}
