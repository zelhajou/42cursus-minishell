/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 22:50:11 by zelhajou          #+#    #+#             */
/*   Updated: 2022/11/19 21:26:00 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Description : Adds the node ’new’ at the beginning of the list.
	
	lst:	The address of a pointer to the first link of a list.
	new:	The address of a pointer to the node to be added to the list.
*/

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	if (!lst)
	{
		*lst = new;
		return ;
	}
	new->next = *lst;
	*lst = new;
}
