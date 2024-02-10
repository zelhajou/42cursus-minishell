/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 11:06:01 by zelhajou          #+#    #+#             */
/*   Updated: 2022/11/19 21:09:52 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Description : Allocates (with malloc(3)) and returns an array of strings 
	obtained by splitting ’s’ using the character ’c’ as a delimiter.
	The array must end with a NULL pointer.

	s:	The string to be split.
	c:	The delimiter character.
*/

#include "libft.h"

static char	**ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free (str[i]);
		i++;
	}
	free (str);
	str = NULL;
	return (str);
}

static int	count_word(char const *s, char c)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 0;
	while (s[i])
	{
		if (s[i] != c && flag == 0)
		{
			j++;
			flag = 1;
		}
		else if (s[i] == c && flag == 1)
			flag = 0;
		i++;
	}
	return (j);
}

static int	count_char(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[j] != c)
			j++;
		i++;
	}
	return (j);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**ptr;
	int		number_word;
	int		number_char;

	i = 0;
	number_char = 0;
	if (!s)
		return (NULL);
	number_word = count_word(s, c);
	ptr = (char **)malloc(sizeof(char *) * (number_word + 1));
	if (!ptr)
		return (NULL);
	while (i < number_word)
	{
		while (*s == c)
			s++;
		number_char = count_char(s, c);
		ptr[i] = ft_substr(s, 0, number_char);
		if (!ptr[i])
			ptr = ft_free(ptr);
		s += number_char;
		i++;
	}
	return (ptr[i] = NULL, ptr);
}
