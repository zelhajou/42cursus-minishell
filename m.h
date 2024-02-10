#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

typedef		struct	tre
{
	char				*val;
	struct		tre		*right;
	struct		tre		*left;
	struct		tre		*prev;
}						s_tree;

int				general_execution(s_tree *head, char **env);
