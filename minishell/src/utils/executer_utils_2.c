#include "minishell.h"

char	*adapt_quoted_str(char *str)
{
	char				*new_str;
	int				a;
	int				b;

	a = 0;
	b = sizeof_str(str, '\0');
	if (str && str[0] == '"' && str[b - 1] == '"')
	{
		a += 1;
		b -= 1;
	}
	new_str = malloc((b - a) + 1);
	s_strcopy(new_str, str, a, b);
	free(str);
	return (new_str);
}

char	**merge_it(char **f_args, char **_cmd_)
{
	int				a;
	char				**new_args;

	if (!f_args)
		return (NULL);
	a = 1;
	while (_cmd_[a])
		a++;
	new_args = malloc((a + 1) * sizeof(char *));
	a = 0;
	new_args[a] = adapt_quoted_str(strcopy(f_args[a]));
	while (_cmd_[++a])
		new_args[a] = adapt_quoted_str(strcopy(_cmd_[a]));
	new_args[a] = 0;
	free_multible(f_args);
	for (int i=0;new_args[i];i++)
		printf("args[%i]: .%s.\n", i, new_args[i]);
	printf("\n");
	return (new_args);
}

char	*corrected_statment(char *s_1, char *s_2, char *s_3)
{
	char				*new_statment;
	int				b[3];
	int				c;
	int				a;

	a = 0;
	b[0] = sizeof_str(s_1, '\0');
	b[1] = sizeof_str(s_2, '\0');
	b[2] = 0;
	if (s_3)
		b[2] = sizeof_str(s_3, '\0');
	c = b[0] + b[1] + b[2] + 3;
	new_statment = malloc(c);
	s_strcopy(new_statment, s_1, 0, b[0]);
	s_strcopy(new_statment + b[0], s_2, 0, b[1]);
	if (s_3)
		s_strcopy(new_statment + b[0] + b[1], s_3, 0, b[2]);
	return (new_statment);
}

// a = a + 1 || a = (a + 1) + (a + 2)

char	**adapt_export_statments(char **new_statment, char **_cmd)
{
	int				a[2];
	int				c;

	a[0] = 1;
	a[1] = 1;
	while (_cmd[a[0]])
	{
		c = sizeof_str(_cmd[a[0]], '\0');
		if (_cmd[a[0]][c - 1] == '=' && _cmd[a[0] + 1]
			&& !str_cmp(_cmd[a[0] + 1], "=", NULL))
		{
			new_statment[a[1]] = corrected_statment(_cmd[a[0]], _cmd[a[0] + 1], NULL);
			a[0] += 1;
		}
		else if (_cmd[a[0] + 1] && _cmd[a[0] + 2]
			&& !str_cmp(_cmd[a[0]], "=", NULL) 
			&& str_cmp(_cmd[a[0] + 1], "=", NULL) 
			&& !str_cmp(_cmd[a[0] + 2], "=", NULL))
		{
			new_statment[a[1]] = corrected_statment(_cmd[a[0]], _cmd[a[0] + 1], _cmd[a[0] + 2]);
			a[0] += 2;
		}
		else
			new_statment[a[1]] = strcopy(_cmd[a[0]]);
		//printf("passed: .%s.\n",   new_statment[a[1]]);
		a[0]++;
		a[1]++;
	}
	new_statment[a[1]] = 0;
	return (new_statment);
}

char	**misstatment_detector(char **_cmd)
{
	int				b;
	char				**new_statment;

	b = sizeof_arr(_cmd);
	if (b <= 2)
		return (_cmd);
	new_statment = malloc((b + 1) * sizeof(char *));
	new_statment[0] = strcopy(_cmd[0]);
	new_statment = adapt_export_statments(new_statment, _cmd);
	//>
	//for (int i=0;new_statment[i];i++)
	//	printf("new[%i]: .%s.\n", i, new_statment[i]);
	free_multible(_cmd);
	return (new_statment);
}
