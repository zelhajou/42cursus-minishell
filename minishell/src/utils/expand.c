#include "minishell.h"

int	isvalid_var_start(char *str, int index, int con)
{
	if ((con && str[index] == '$'
		&& str[index + 1]
		&& str[index + 1] != '$'
		&& !ft_isspace(str[index + 1])
		&& ft_isalnum(str[index + 1]))
		|| (!con && str[index]
		&& str[index] != '$'
		&& !ft_isspace(str[index])
		&& ft_isalnum(str[index])))
		return (1);
	return (0);
}

char	*_transformed_var(char *old_var, char *__new, int st, int end)
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

char	*_transform_var(char *var, s_en *env, int a, int b)
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
		return (_transformed_var(var, env->env__[c][1], a, b));
	else
		return (_transformed_var(var, " ", a, b));
}

char	*_catch_var(char *var, s_en *env)
{
	int							a;
	int							b;

	a = 0;
	while (var[a])
	{
		if (isvalid_var_start(var, a, 1))
		{
			b = a + 1;
			while (isvalid_var_start(var, b, 0))
				b++;
			return (_catch_var(
					_transform_var(var, env, a, b),
					env));
		}
		a++;
	}
	return (var);
}

void	_expand_it(t_ast_node *head, s_en *env)
{
	int							a;

	if (head->file_type != F_R && head->args)
	{
		a = 0;
		while (head->args[a])
		{
			head->args[a] = _catch_var(head->args[a], env);
			a++;
		}
	}
	if (head->left)
		_expand_it(head->left, env);
	if (head->right)
		_expand_it(head->right, env);
}
