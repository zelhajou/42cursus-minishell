/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 23:11:51 by zelhajou          #+#    #+#             */
/*   Updated: 2022/11/19 21:18:35 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Description : Outputs the character ’c’ to the given file descriptor.

	c:  The character to output.
	fd:  The file descriptor on which to write.
*/

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
