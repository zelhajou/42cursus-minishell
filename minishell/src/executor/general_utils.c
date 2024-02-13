#include "../../includes/minishell.h"

void	close_fd(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
}

int	sizeof_str(char *str, char end)
{
	int			a;

	a = 0;
	while (str[a] != '\0' && str[a] != end)
		a += 1;
	return (a);
}

char	*strcopy(char *src)
{
	int					a;
	int					b;
	char				*dest;

	b = 0;
	while (src[b])
		b += 1;
	dest = malloc(b + 1);
	a = 0;
	while (a < b)
	{
		dest[a] = src[a];
		a += 1;
	}
	dest[a] = '\0';
	return (dest);
}

int		str_cmp(char *s_1, char *s_2, char *s_3)
{
	int					a;

	a = 0;
	while (s_1[a] && s_2[a] && s_1[a] == s_2[a])
		a += 1;
	if (a == sizeof_str(s_1, '\0')
		&& a == sizeof_str(s_2, '\0'))
		return (1);
	if (s_3)
		return (str_cmp(s_1, s_3, NULL));
	return (0);
}

int	is_red(char *str)
{
	if (str_cmp(str, "|", NULL) || str_cmp(str, ">", ">>")
			|| str_cmp(str, "<", "<<"))
		return (1);
	return (0);
}
