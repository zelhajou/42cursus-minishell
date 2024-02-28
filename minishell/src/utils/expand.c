/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:17:44 by beddinao          #+#    #+#             */
/*   Updated: 2024/02/28 00:06:15 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_variable_start(char *str, int index, int con)
{
	if ((con && str[index] == '$'
			&& str[index + 1]
			&& str[index + 1] != '$'
			&& !ft_isspace(str[index + 1])
			&& (ft_isalnum(str[index + 1])
				|| str[index + 1] == '_'
				|| str[index + 1] == '?'))
		|| (!con && str[index]
			&& str[index] != '$'
			&& !ft_isspace(str[index])
			&& (ft_isalnum(str[index])
				|| str[index] == '_'
				|| str[index] == '?')))
		return (1);
	return (0);
}

char	*replace_variable_with_value(char *old_var, char *__new, int st, int end)
{
	int							size;
	char						*new__;
	int							unsize;

	unsize = sizeof_str(__new, '\0');
	size = st + (sizeof_str(old_var, '\0') - end) + unsize;
	new__ = malloc(size + 1);
	s_strcopy(new__, old_var, 0, st);
	s_strcopy(new__ + st, __new, 0, unsize);
	s_strcopy(new__ + st + unsize, old_var, end, sizeof_str(old_var, '\0'));
	free(old_var);
	return (new__);
}

char	*expand_variable_in_string(char *var, t_env *env, int a, int b)
{
	int							hole_size;
	int							c;
	char						*new_var;

	hole_size = b - a;
	new_var = malloc(hole_size + 1);
	s_strcopy(new_var, var, a + 1, b);
	c = get_env_index(env, new_var);
	free(new_var);
	if (c >= 0)
		return (replace_variable_with_value(var, env->parsed_env[c][1], a, b));
	else
		return (replace_variable_with_value(var, "", a, b));
}

char	*recursively_expand_variables(char *var, t_env *env)
{
	int							a;
	int							b;
	int							si_q_count;

	a = 0;
	si_q_count = 0;
	while (var[a])
	{
		if (var[a] == 39)
			si_q_count++;
		if (!(si_q_count % 2)
			&& is_valid_variable_start(var, a, 1))
		{
			b = a + 1;
			while (is_valid_variable_start(var, b, 0))
				b++;
			return (recursively_expand_variables(
					expand_variable_in_string(var, env, a, b),
					env));
		}
		a++;
	}
	return (var);
}

void	expand_variables_in_ast(t_ast_node *head, t_env *env)
{
	int							a;

	if (head->file_type != F_R && head->args)
	{
		a = 0;
		while (head->args[a])
		{
			head->args[a] = recursively_expand_variables(head->args[a], env);
			a++;
		}
	}
	if (head->left)
		expand_variables_in_ast(head->left, env);
	if (head->right)
		expand_variables_in_ast(head->right, env);
}
