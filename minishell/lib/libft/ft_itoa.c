/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:29:47 by zelhajou          #+#    #+#             */
/*   Updated: 2022/11/20 22:28:28 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Description : Allocates (with malloc(3)) and returns a string representing
	the integer received as an argument. Negative numbers must be handled.

	n:  the integer to convert.
*/
#include "libft.h"

static int	count_char(long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	else if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*str;
	int		number;
	long	nb;

	i = 0;
	nb = n;
	number = count_char(n) - 1;
	str = (char *)ft_calloc((count_char(n) + 1), sizeof(char));
	if (!str)
		return (NULL);
	if (n < 0)
		nb *= -1;
	while (number >= 0)
	{
		str[number] = (nb % 10) + '0';
		nb = nb / 10;
		number--;
		i++;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
