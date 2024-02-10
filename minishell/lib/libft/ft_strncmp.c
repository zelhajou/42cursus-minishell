/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:38:34 by zelhajou          #+#    #+#             */
/*   Updated: 2022/11/19 20:43:25 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
    ft_strcmp() compares the two strings s1 and s2. It returns an integer less
	than, equal to, or greater than zero if s1 is found, respectively, 
	to be less than, to match, or be greater than s2.
	
	ft_strncmp() is similar, except it only compares the first (at most) n bytes 
	of s1 and s2.
*/

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
