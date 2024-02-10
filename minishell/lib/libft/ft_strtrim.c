/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 07:48:23 by zelhajou          #+#    #+#             */
/*   Updated: 2022/11/19 21:08:41 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Descriptin : Allocates (with malloc(3)) and returns a copy of ’s1’ with the 
	characters specified in ’set’ removed from the beginning and the end of 
	the string.

	s1:		The string to be trimmed.
	set:	The reference set of characters to trim.
*/

#include "libft.h"

static int	first_set(const char *s1, const char *set)
{
	int	i;
	int	c;
	int	j;

	i = 0;
	while (s1[i] != '\0')
	{
		c = 0;
		j = 0;
		while (set[j] != '\0')
		{
			if (set[j] == s1[i])
				c++;
			j++;
		}
		if (c == 0)
			return (i);
		i++;
	}
	return (i);
}

static int	last_set(const char *s1, const char *set)
{
	int	c;
	int	j;
	int	len;

	len = ft_strlen(s1);
	while (len--)
	{
		c = 0;
		j = 0;
		while (set[j] != '\0')
		{
			if (set[j] == s1[len])
				c++;
			j++;
		}
		if (c == 0)
			return (len);
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	int		i;
	int		first;
	int		last;

	i = 0;
	if (!s1)
		return (NULL);
	first = first_set(s1, set);
	last = last_set(s1, set);
	if (first > last)
		return (ft_strdup(""));
	ptr = (char *)malloc(sizeof(char) * ((last - first) + 2));
	if (ptr == NULL)
		return (NULL);
	while (first <= last)
	{
		ptr[i] = s1[first];
		first++;
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
