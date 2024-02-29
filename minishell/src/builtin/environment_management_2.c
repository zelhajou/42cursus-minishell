/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_management_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beddinao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:37:57 by beddinao          #+#    #+#             */
/*   Updated: 2024/02/29 17:38:17 by beddinao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_just_print(t_env *env, int con, int *_out_fd)
{
	int					a;

	a = 0;
	while (env->parsed_env[a])
	{
		if (con && !str_cmp(env->parsed_env[a][0], "?", NULL))
			print_export_declaration_to_fd(
				env->parsed_env[a][0], env->parsed_env[a][1], _out_fd[1]);
		else if (!str_cmp(env->parsed_env[a][0], "?", NULL))
			print_env_var_to_fd(
				env->parsed_env[a][0], env->parsed_env[a][1], _out_fd[1]);
		a++;
	}
	return (0);
}
