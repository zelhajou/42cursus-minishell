/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:17:44 by beddinao          #+#    #+#             */
/*   Updated: 2024/02/29 18:57:08 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_variable_with_value(
		char *old_var, char *__new, int st, int end)
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

char	*expand_variable_in_string(char *var, t_env *env, int a)
{
	int							hole_size;
	int							c;
	int							b;
	char						*new_var;

	b = a + 1;
	while (is_valid_variable_start(var, b, 0))
		b++;
	hole_size = b - a;
	new_var = malloc(hole_size + 1);
	s_strcopy(new_var, var, a + 1, b);
	c = find_env_var_index(env, new_var);
	free(new_var);
	if (c >= 0)
		return (replace_variable_with_value(var, env->parsed_env[c][1], a, b));
	else
		return (replace_variable_with_value(var, "", a, b));
}

char	*recursively_expand_variables(char *var, t_env *env, int __con)
{
	int							a;
	int							si_q_count;
	int							do_q_count;

	a = 0;
	si_q_count = 0;
	do_q_count = 0;
	while (var[a])
	{
		if (var[a] == 39)
		{
			a++;
			si_q_count++;
			while (!(do_q_count % 2) && var[a] && var[a] != 39)
				a++;
		}
		if (var[a] == 34)
			do_q_count++;
		if (is_valid_variable_start(var, a, 1)
			&& (!(do_q_count % 2) || !__con))
			return (recursively_expand_variables(
					expand_variable_in_string(var, env, a), env, __con));
		a++;
	}
	return (var);
}

char	**refactore_args_array(char **args)
{
	int						a;
	int						b;
	int						c;
	char					**new_args;

	a = 0;
	b = 0;
	c = count_strings_in_array(args);
	new_args = malloc((detected_flaws(args) + c + 1) * sizeof(char **));
	while (args[a])
	{
		c = is_flawed_str(args[a], 0, 0, 0);
		if (c)
			simplified_refactor_thing(new_args, &b, args[a]);
		else
			new_args[b] = strcopy(args[a]);
		a++;
		b++;
	}
	new_args[b] = 0;
	free_string_array(args);
	return (new_args);
}

void	expand_variables_in_ast(t_ast_node *head, t_env *env)
{
	int							a;

	if (head->file_type != FILE_READY && head->args)
	{
		a = -1;
		while (head->args[++a])
			head->args[a] = recursively_expand_variables(head->args[a], env, 1);
		head->args = refactore_args_array(head->args);
		a = 0;
		while (head->args[a])
		{
			head->args[a] = recursively_expand_variables(head->args[a], env, 0);
			head->args[a] = remove_quotes_from_str(head->args[a]);
			a++;
		}
	}
	if (head->left)
		expand_variables_in_ast(head->left, env);
	if (head->right)
		expand_variables_in_ast(head->right, env);
}
