/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 06:51:24 by zelhajou          #+#    #+#             */
/*   Updated: 2024/02/29 16:21:51 by beddinao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_str_without_quotes(char *new_str, char *old_str, int size)
{
	int					a;
	int					b;

	a = 0;
	b = 0;
	while (old_str && a < size)
	{
		if (old_str[b] != 34 && old_str[b] != 39)
			new_str[a++] = old_str[b];
		b++;
	}
	new_str[a] = '\0';
}

char	*remove_quotes_from_str(char *str)
{
	char				*new_str;
	int					b;
	int					a;
	int					size;

	a = 0;
	size = 0;
	b = sizeof_str(str, '\0');
	while (str && a < b)
	{
		if (str[a] != 34 && str[a] != 39)
			size++;
		a++;
	}
	new_str = malloc(size + 1);
	copy_str_without_quotes(new_str, str, size);
	free(str);
	return (new_str);
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
