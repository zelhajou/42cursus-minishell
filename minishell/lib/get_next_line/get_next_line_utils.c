/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beddinao <beddinao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:26:30 by beddinao          #+#    #+#             */
/*   Updated: 2023/12/10 12:24:15 by beddinao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*re_clean(void *b, size_t i, size_t len)
{
	unsigned char		*ba;

	ba = (unsigned char *)b;
	while (i < len)
	{
		ba[i] = 0;
		i++;
	}
	return (b);
}

void	*re_doit(size_t len)
{
	unsigned char		*sa;

	sa = malloc((len + 1) * sizeof(*sa));
	if (!sa)
		return (NULL);
	sa = re_clean(sa, 0, len + 1);
	return (sa);
}

char	*re_tighten(char *str, int st, int end, int con)
{
	char				*new_str;
	int					i;

	new_str = re_doit(end - st);
	if (!new_str)
		return (NULL);
	i = 0;
	while (st < end)
		new_str[i++] = str[st++];
	if (con)
		free(str);
	return (new_str);
}

char	*re_tightenthem(char *str_1, char *str_2, int end, int end_2)
{
	char				*new_str;
	int					i;
	int					j;

	new_str = re_doit(end + end_2);
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < end)
	{
		new_str[i] = str_1[i];
		i++;
	}
	j = 0;
	while (j < end_2)
		new_str[i++] = str_2[j++];
	free(str_1);
	free(str_2);
	return (new_str);
}

int	is_divided(char *str, int st, int size)
{
	int					i;

	i = st;
	while (1)
	{
		if (i == size || str[i++] == '\n')
			break ;
	}
	return (i);
}
