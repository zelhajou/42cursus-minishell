/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termination.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:20:49 by beddinao          #+#    #+#             */
/*   Updated: 2024/02/28 00:06:15 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_environment_variables(t_env *env)
{
	int				a;

	a = 0;
	while (env->parsed_env[a])
	{
		free(env->parsed_env[a][0]);
		free(env->parsed_env[a][1]);
		free(env->parsed_env[a]);
		a += 1;
	}
	free(env->parsed_env);
	free(env);
}

void	cleanup_and_exit_shell(t_env *env, int status)
{
	if (env)
	{
		free_string_array(env->original_env);
		free_environment_variables(env);
	}
	exit(status);
}

void	free_string_array(char **arr)
{
	int				a;

	a = 0;
	while (arr[a] != 0)
	{
		free(arr[a]);
		a += 1;
	}
	free(arr);
}

void	close_pipe_ends(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
}
