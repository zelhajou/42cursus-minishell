#include "../../includes/exec.h"

char	*translate_var(char *line, s_en *env, int i_ndx)
{
	int						a;
	int						b;
	char					*new_var;

	a = i_ndx;
	while (line[a] && line[a] != ' '
		&& line[a] != '$' && line[a] != '/')
		a++;
	new_var = malloc((a - i_ndx) + 1);
	s_strcopy(new_var, line, i_ndx, a);
	b = get_env_index(env, new_var);
	free(new_var);
	if (b >= 0)
		return (strcopy(env->env__[b][1]));
	return (strcopy(" "));
}

char	*replace_line(char *line, char *env_var, int index)
{
	char					*new_line;
	int						var_size;
	int						hole_size;
	int						v_in;
	int						l_in;

	v_in = 0;
	l_in = index - 1;
	hole_size = index;
	while (line[hole_size] && line[hole_size] != ' '
		&& line[hole_size] != '$' && line[hole_size] != '/')
		hole_size += 1;
	hole_size -= index;
	var_size = sizeof_str(env_var, '\0');
	new_line = malloc((sizeof_str(line, '\0') - hole_size) + var_size);
	s_strcopy(new_line, line, 0, index - 1);
	while (v_in < var_size)
		new_line[l_in++] = env_var[v_in++];
	while (line[index + hole_size])
		new_line[l_in++] = line[index++ + hole_size];
	new_line[l_in] = '\0';
	return (new_line);
}

char	*expand_it(char *line, s_en *env)
{
	int						a;
	int						s;
	char					*env_var;
	char					*new_line;

	a = 0;
	s = sizeof_str(line, '\0');
	while (a < s)
	{
		if (line[a] == '$'
				&& line[a + 1]
				&& line[a + 1] != ' '
				&& line[a + 1] != '\n'
				&& line[a + 1] != '\t'
				&& line[a + 1] != '$')
		{
			env_var = translate_var(line, env, a + 1);
			new_line = replace_line(line, env_var, a + 1);
			free(line);
			free(env_var);
			return (expand_it(new_line, env));
		}
		a++;
	}
	return (line);
}
