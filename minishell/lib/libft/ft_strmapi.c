/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 01:03:10 by zelhajou          #+#    #+#             */
/*   Updated: 2022/11/21 02:54:27 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Description : Applies the function ’f’ to each character of the string ’s’,
	and passing its index as first argument to create a new string 
	(with malloc(3)) resulting from successive applications of ’f’.

	s:	The string on which to iterate.
	f:	The function to apply to each character.
*/

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*str;

	if (!s || !f)
		return (0);
	i = 0;
	str = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
