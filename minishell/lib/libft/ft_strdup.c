/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:03:07 by zelhajou          #+#    #+#             */
/*   Updated: 2022/11/19 20:43:10 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	strdup() returns a pointer to a new string which is a duplicate 
	of the string s.  Memory for the new string is obtained with malloc.
*/

#include "libft.h"

char	*ft_strdup(const char *src)
{
	size_t	i;
	size_t	size;
	char	*str;

	i = 0;
	size = ft_strlen(src);
	str = malloc(size + 1);
	if (str == NULL)
		return (NULL);
	while (src[i])
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
