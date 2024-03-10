/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beddinao <beddinao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:59:58 by beddinao          #+#    #+#             */
/*   Updated: 2024/03/10 09:46:27 by beddinao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_new_pwd_in_env(char *new_, t_env *env, int c)
{
	char				**exp_pwd;
	int					a;
	int					b;

	a = 0;
	b = 4;
	(void)c;
	exp_pwd = malloc(3 * sizeof(char *));
	if (!exp_pwd)
		return ;
	exp_pwd[0] = strcopy("export");
	exp_pwd[1] = malloc(sizeof_str(new_, '\0') + 5);
	if (!exp_pwd[1])
		return ;
	s_strcopy(exp_pwd[1], "PWD=", 0, 4);
	while (new_[a])
		exp_pwd[1][b++] = new_[a++];
	exp_pwd[1][b] = '\0';
	exp_pwd[2] = 0;
	unset_or_export_cmd(exp_pwd, env, NULL, &a);
	free_string_array(exp_pwd);
}

int	change_current_directory(char *path, t_env *env)
{
	int					status;
	int					a;

	if (!path || !sizeof_str(path, '\0'))
	{
		a = find_env_var_index(env, "HOME");
		if (a >= 0)
			status = chdir(env->parsed_env[a][1]);
		else
			status = -1;
	}
	else
		status = chdir(path);
	return (status);
}

char	*get_current_working_directory(int size, int tries, int fd)
{
	char				*buffer;

	buffer = malloc(size);
	if (!buffer)
		return (NULL);
	if (!getcwd(buffer, size))
	{
		free(buffer);
		if (tries < 10)
			return (get_current_working_directory(size + 50, tries + 1, fd));
		else
		{
			ft_putendl_fd("  err: cd() / pwd(): getcwd(): you are lost", fd);
			return (NULL);
		}
	}
	return (buffer);
}

char	***sort_tha_array(char ***_array, int _si)
{
	int					a;
	int					b;
	int					c;
	char				**temp_p;

	a = 0;
	while (a < _si - 1)
	{
		b = a + 1;
		c = string_weight_compare(_array[a][0], _array[b][0]);
		if (c)
		{
			temp_p = _array[a];
			_array[a] = _array[b];
			_array[b] = temp_p;
		}
		a++;
	}
	if (check_array_arrangment(_array, _si))
		return (_array);
	return (sort_tha_array(_array, _si));
}

void	print_export_declaration_to_fd(t_env *env, int *_out_fd)
{
	char				***new_array;
	int					a;

	a = 0;
	while (env->parsed_env[a] != 0)
		a++;
	if (!a)
		return ;
	new_array = duplicate_env_structure(env, a, 'F', -1);
	new_array[a] = 0;
	new_array = sort_tha_array(new_array, a);
	print_export_vars(new_array, a, _out_fd[1]);
	free_environment_variables(new_array);
}
