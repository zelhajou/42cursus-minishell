/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:03:19 by beddinao          #+#    #+#             */
/*   Updated: 2024/02/27 23:27:30 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_subpath_from_var(char *env_var, char *file, int *indx_s)
{
	char		*tmp_path;
	int			a;
	int			b;
	int			file_size;

	increment_path_index(env_var, indx_s, &a);
	file_size = sizeof_str(file, ' ');
	tmp_path = malloc((indx_s[1] - a) + file_size + 2);
	if (!tmp_path)
		return (NULL);
	b = 0;
	while (b < ((indx_s[1] - a) + file_size + 1))
	{
		if (indx_s[3] && (b < indx_s[1] - a))
			tmp_path[b] = env_var[a + b];
		else if (indx_s[3]
			&& env_var[indx_s[1] - 1] != '/'
			&& (b == indx_s[1] - a))
			tmp_path[b] = '/';
		else
			tmp_path[b] = file[b - (indx_s[1] - a) - indx_s[3]];
		b++;
	}
	tmp_path[b] = '\0';
	return (tmp_path);
}

char	*verify_path_without_env(char *file, int mode)
{
	char				*tmp_path;
	int					b;

	b = sizeof_str(file, ' ');
	tmp_path = malloc(b + 1);
	if (!tmp_path)
		return (NULL);
	s_strcopy(tmp_path, file, 0, b);
	if (is_path_accessible(tmp_path, mode))
		return (tmp_path);
	free(tmp_path);
	return (NULL);
}

char	*fetch_file_path(char *file, char **envp, char *env_var, int mode)
{
	char				*tmp_path;
	int					indx_s[4];

	indx_s[3] = 0;
	indx_s[1] = sizeof_str(env_var, '\0');
	indx_s[0] = find_substr_index(envp, env_var, indx_s[1]);
	if (indx_s[0] < 0
		|| (file[0] && file[1] && file[0] == '.' && file[1] == '/'))
		return (verify_path_without_env(file, mode));
	indx_s[2] = sizeof_str(envp[indx_s[0]], '\0');
	if (sizeof_str(file, ' ') != sizeof_str(file, '\0')
			&& !is_path_accessible(file, mode))
		return (NULL);
	while (envp[indx_s[0]][indx_s[1]])
	{
		tmp_path = create_subpath_from_var(envp[indx_s[0]], file, indx_s);
		if (!tmp_path)
			return (NULL);
		if (is_path_accessible(tmp_path, mode))
			return (tmp_path);
		free(tmp_path);
		if (!indx_s[3])
			indx_s[3] = 1;
	}
	return (NULL);
}

char	*find_next_substring(char *str, char del, int *index)
{
	char		*sub;
	int			size;
	int			a;

	while (str[index[0]] && str[index[0]] == del)
		index[0] += 1;
	size = sizeof_str(str + index[0], del);
	sub = malloc(size + 1);
	if (!sub)
		return (NULL);
	a = 0;
	while (str[index[0]]
		&& str[index[0]] != del)
	{
		if (str[index[0]] != 34 && str[index[0]] != 39)
			sub[a++] = str[index[0]];
		index[0] += 1;
	}
	sub[a] = '\0';
	index[0] += 1;
	return (sub);
}

char	**prepare_cmd_arguments(char *cmd, char **envp, int c)
{
	char		**cmd_arr;
	char		*cmd_holder;
	int			i[3];

	i[1] = count_substrings(cmd, ' ');
	cmd_arr = malloc((i[1] + 1) * sizeof(char *));
	if (!cmd_arr)
		return (NULL);
	i[0] = 0;
	while (c < i[1])
	{
		cmd_holder = find_next_substring(cmd, '\0', i);
		if (!c && !check_if_command_is_builtin(cmd_holder))
		{
			cmd_arr[c] = fetch_file_path(cmd_holder, envp, "PATH", X_OK);
			free(cmd_holder);
		}
		else
			cmd_arr[c] = cmd_holder;
		if (!cmd_arr[c])
			return (NULL);
		c += 1;
	}
	cmd_arr[c] = NULL;
	return (cmd_arr);
}
