/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 03:55:53 by zelhajou          #+#    #+#             */
/*   Updated: 2022/11/19 20:42:49 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	ft_memchr() scans the initial n bytes of the memory area pointed to by s 
	for the first instance of c.  Both c and the bytes of the memory area 
	pointed to by s are interpreted as unsigned char.
*/

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*obj;

	i = 0;
	obj = (unsigned char *)s;
	while (i < n)
	{
		if (obj[i] == (unsigned char)c)
			return (&obj[i]);
		i++;
	}
	return (0);
}
