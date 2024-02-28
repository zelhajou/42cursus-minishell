/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:59:58 by beddinao          #+#    #+#             */
/*   Updated: 2024/02/28 17:13:56 by zelhajou         ###   ########.fr       */
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
	exp_pwd[0] = strcopy("export");
	exp_pwd[1] = malloc(sizeof_str(new_, '\0') + 5);
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

void	print_env_var_to_fd(char *str_1, char *str_2, int fd)
{
	if (!str_cmp(str_2, "F1", NULL))
	{
		ft_putstr_fd(str_1, fd);
		ft_putstr_fd(" : ", fd);
		if (str_2[0])
			ft_putstr_fd(str_2, fd);
		write(fd, "\n", 1);
	}
}

void	print_export_declaration_to_fd(char *str_1, char *str_2, int fd)
{
	ft_putstr_fd("declare -x ", fd);
	ft_putstr_fd(str_1, fd);
	if (!str_cmp(str_2, "F1", NULL))
	{
		write(fd, "=", 1);
		ft_putchar_fd('"', fd);
		if (str_2[0])
			ft_putstr_fd(str_2, fd);
		ft_putchar_fd('"', fd);
	}
	write(fd, "\n", 1);
}
