/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:00:21 by zelhajou          #+#    #+#             */
/*   Updated: 2022/11/19 21:23:23 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Description : Allocates (with malloc(3)) and returns a new node. The member 
	variable ’content’ is initialized with the value of the parameter ’content’.
	The variable ’next’ is initialized to NULL.

	content: The content to create the node with.
*/

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
