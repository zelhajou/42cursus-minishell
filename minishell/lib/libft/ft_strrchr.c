/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:29:24 by zelhajou          #+#    #+#             */
/*   Updated: 2022/11/19 20:43:29 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	ft_strrchr() returns a pointer to the last occurrence
	of the character c in the string s
*/

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	size;

	size = ft_strlen(s);
	while (size >= 0)
	{
		if (s[size] == (char)c)
			return ((char *)s + size);
		size--;
	}
	return (0);
}
