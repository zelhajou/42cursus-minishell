/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:59:51 by zelhajou          #+#    #+#             */
/*   Updated: 2022/11/19 20:43:37 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	ft_toupper() converts the letter c to upper case, if possible.
*/

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
