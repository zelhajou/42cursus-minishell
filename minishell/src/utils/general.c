/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beddinao <beddinao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:14:59 by beddinao          #+#    #+#             */
/*   Updated: 2024/02/27 10:19:32 by beddinao         ###   ########.fr       */
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

char	*strcopy(char *src)
{
	int					a;
	int					b;
	char				*dest;

	b = 0;
	while (src[b])
		b += 1;
	dest = malloc(b + 1);
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
