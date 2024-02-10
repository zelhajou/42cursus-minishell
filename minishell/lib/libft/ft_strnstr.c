/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:03:39 by zelhajou          #+#    #+#             */
/*   Updated: 2022/11/19 20:43:27 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
	ft_strnstr() Find the first substring in a length-limited string
	big:	The string to be searched
	little:	The string to search for
	len:	the maximum number of characters to search
*/

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[i] == '\0')
		return ((char *) big);
	while ((big[i] != '\0') && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && (i + j) < len)
		{
			if (little[j + 1] == '\0')
				return ((char *)big + i);
			j++;
		}
		i++;
	}
	return (0);
}
