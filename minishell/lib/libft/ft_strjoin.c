/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 18:11:35 by zelhajou          #+#    #+#             */
/*   Updated: 2022/11/19 21:06:18 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Description : Allocates (with malloc(3)) and returns a new string, 
	which is the result of the concatenation of ’s1’ and ’s2’.
	
	s1:	The prefix string.
	s2:	The suffix string.
*/

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = -1;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (len--)
	{
		if (s1[i])
		{
			str[i] = s1[i];
			i++;
		}
		else if (s2[++j])
			str[i + j] = s2[j];
	}
	str[i + j + 1] = '\0';
	return (str);
}
