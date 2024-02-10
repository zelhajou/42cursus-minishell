/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 03:19:24 by zelhajou          #+#    #+#             */
/*   Updated: 2022/11/19 21:22:16 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Description : Outputs the integer ’n’ to the given file descriptor.

	n:	The integer to output.
	fd:	The file descriptor on which to write.
*/

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long long	nbr;

	nbr = n;
	if (nbr < 0)
	{
		ft_putchar_fd('-', fd);
		nbr = nbr * -1;
	}
	if (nbr > 9)
		ft_putnbr_fd((nbr / 10), fd);
	write(fd, &"0123456789"[nbr % 10], 1);
}
