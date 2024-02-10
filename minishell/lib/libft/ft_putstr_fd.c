/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 02:22:59 by zelhajou          #+#    #+#             */
/*   Updated: 2022/11/19 21:19:27 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Description : Outputs the string ’s’ to the given file descriptor.

	s:	The string to output.
	fd:	The file descriptor on which to write.
*/

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	while (*s != '\0')
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
}
