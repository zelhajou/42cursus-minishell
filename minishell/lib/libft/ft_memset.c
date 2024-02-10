/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:28:07 by zelhajou          #+#    #+#             */
/*   Updated: 2022/11/19 20:42:55 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
	ft_memset() sets the first len bytes of the memory area pointed to by 
	s to the value specified by c
*/

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*obj;

	i = 0;
	obj = (unsigned char *)s;
	while (i < n)
	{
		obj[i] = (unsigned char)c;
		i++;
	}
	return (obj);
}
