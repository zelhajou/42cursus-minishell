/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:15:57 by zelhajou          #+#    #+#             */
/*   Updated: 2022/11/19 20:42:19 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	ft_isalnum() checks for an alphanumeric character; 
	it is equivalent to (ft_isalpha(c) || ft_isdigit(c)).
*/

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}
