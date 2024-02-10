/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 19:31:40 by zelhajou          #+#    #+#             */
/*   Updated: 2022/11/21 03:30:39 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
	ft_memcpy() function copies n bytes from memory area src to memory area dest
*/

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	i = 0;
	if (!dst && !src)
		return (0);
	s1 = (unsigned char *)dst;
	s2 = (unsigned char *)src;
	if (s1 == s2)
		return (s1);
	while (i < n)
	{
		s1[i] = s2[i];
		i++;
	}
	return (s1);
}
