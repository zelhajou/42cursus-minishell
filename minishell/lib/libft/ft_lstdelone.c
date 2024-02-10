/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:31:28 by zelhajou          #+#    #+#             */
/*   Updated: 2022/11/19 21:29:25 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Description : Takes as a parameter a node and frees the memory of 
	the node’s content using the function ’del’ given as a parameter and free 
	the node.  The memory of ’next’ must not be freed.

	lst:  The node to free.
	del:  The address of the function used to delete the content.
*/

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst)
		return ;
	del(lst->content);
	free(lst);
}
