/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:12:09 by beddinao          #+#    #+#             */
/*   Updated: 2024/02/28 15:54:33 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**merge_command_args(char **f_args, char **_cmd_)
{
	int				a;
	char			**new_args;

	if (!f_args)
		return (NULL);
	a = 1;
	while (_cmd_[a])
		a++;
	new_args = malloc((a + 1) * sizeof(char *));
	a = 0;
	new_args[a] = strcopy(f_args[a]);
	while (_cmd_[++a])
		new_args[a] = strcopy(_cmd_[a]);
	new_args[a] = 0;
	free_string_array(f_args);
	return (new_args);
}
