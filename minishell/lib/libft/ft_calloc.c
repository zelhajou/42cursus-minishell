/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 13:12:49 by zelhajou          #+#    #+#             */
/*   Updated: 2022/11/19 20:42:17 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	ft_calloc() — Allocates the space for elements of an array. 
	Initializes the elements to zero and returns a pointer to the memory.
*/

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, (nmemb * size));
	return (ptr);
}
