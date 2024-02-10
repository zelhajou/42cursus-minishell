/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 03:26:49 by zelhajou          #+#    #+#             */
/*   Updated: 2022/11/21 03:05:32 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Description : Applies the function ’f’ on each character of the string 
	passed as argument, passing its index as first argument.
	Each character is passed by address to ’f’ to be modified if necessary.

	s:	The string on which to iterate.
	f:	The function to apply to each character.
*/

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i])
	{
		f(i, &(s[i]));
		i++;
	}
}
