#include "../../includes/exec.h"

void	env_replace_var(char *var, s_en *env)
{
	int				c;
	int				o;
	char			*env_var;

	c = sizeof_str(var, '=');
	env_var = malloc(c + 1);
	s_strcopy(env_var, var, 0, c);
	o = get_env_index(env, env_var);
	if (o >= 0)
		env_minus_one(env, o);
	free(env_var);
	if (c > 0 && c < sizeof_str(var, '\0') - 1)
		env_plus_one(env, var, c, 1);
	else if (var[c] == '=' || c == sizeof_str(var, '\0'))
		env_plus_one(env, var, c, 0);
}

void	adapt_status_env(s_en *env, int status, char *start)
{
	char					*var;
	int					a;

	a = int_size(status) + sizeof_str(start, '\0') + 1;
	var = malloc(a);
	s_strcopy(var, start, 0, sizeof_str(start, '\0'));
	var[--a] = '\0';
	if (!status)
		var[--a] = '0';
	while (status)
	{
		var[--a] = (status % 10) + 48;
		status /= 10;
	}
	env_replace_var(var, env);
	free(var);
}

int	is_space(char *line)
{
	int				a;

	a = 0;
	while (line[a] == ' ' || line[a] == '\t'
		|| line[a] == '\n')
		a += 1;
	if (line[a] == '\0')
		return (1);
	return (0);
}

int	check_line(char **line)
{
	if (*line[0] == '\0' || str_cmp(*line, "\n", NULL) || is_space(*line))
	{
		free(*line);
		return (1);
	}
	return (0);
}

void	ctrl_c_ha(int a)
{
	printf("\n");
	rl_replace_line("", 0);
	rl_redisplay();
}
