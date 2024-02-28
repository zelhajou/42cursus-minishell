/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_managment_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beddinao <beddinao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:53:44 by beddinao          #+#    #+#             */
/*   Updated: 2024/02/28 11:53:46 by beddinao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.c"

char	*str_without_char(char *str, char del)
{
	int				a;
	int				b;
	char				*new_str;

	a = 0;
	b = 0;
	new_str = malloc(sizeof_str(str, '\0') + 1);
	while (str[a])
	{
		if (str[a] != del)
			new_str[b++] = str[a];
		a++;
	}
	new_str[b] = '\0';
	return (new_str);
}
