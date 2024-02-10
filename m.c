#include "m.h"

int		sizeof_sr(char *s_1)
{
	int					a;

	a = 0;
	while (s_1[a])
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

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	s_tree							*head;
	head = malloc(sizeof(s_tree));
	head->prev = NULL;
	head->left = malloc(sizeof(s_tree));
	head->left->prev = head;
	head->left->right = NULL;
	head->left->left = NULL;
	//>
	head->right = malloc(sizeof(s_tree));
	head->right->prev = head;
	head->right->right = malloc(sizeof(s_tree));
	head->right->right->prev = head->right;
	head->right->left = malloc(sizeof(s_tree));
	head->right->left->prev = head->right;
	head->right->left->right = NULL;
	head->right->left->left = NULL;
	head->right->right->right = malloc(sizeof(s_tree));
	head->right->right->left = malloc(sizeof(s_tree));
	head->right->right->right->prev = head->right->right;
	head->right->right->right->right = NULL;
	head->right->right->right->left = NULL;
	head->right->right->left->prev = head->right->right;
	head->right->right->left->right = NULL;
	head->right->right->left->left = NULL;
	/*
	-----val:     input,  	----prev:      <
	-----val:     cat -e,  	----prev:      <
	-----val:     grep ll,  ----prev:      |
	-----val:     outfile,  ----prev:      >

	 								 	>
								          			
								 
						 |					    outfile
									
	 		<				"grep ll"

	input		"cat -e"

	 	< input cat -e | grep ll > outfile

	val: (input);   prev: (<);     < : (1);   | : (1);   > : (1);
	val: (cat -e);   prev: (<);     < : (0);   | : (1);   > : (1);
	val: (grep ll);   prev: (|);     < : (-1);   | : (0);   > : (1);
	val: (outfile);   prev: (>);     < : (-1);   | : (-1);   > : (0);

	*/
	head->val = strcopy("|");
	head->left->val = strcopy("wc");
	head->right->val = strcopy("ls");

	/*head->right->val = strcopy("|");
	head->right->left->val = strcopy("grep ll");
	head->right->right->val = strcopy("<");
	head->right->right->right->val = strcopy("input");
	head->right->right->left->val = strcopy("cat -e");*/
	
	head->right->right = NULL;
	head->right->left = NULL;
	head->left->right = NULL;
	head->left->left = NULL;
	

	// pipe     read_from(0) out_to(1) not(-1)
	
	// in redirection   read_from(0) out_to(1) not (-1)
	
	// out redirection    read_from(0)  out_to(1)   not(-1)
	
	// ?
	general_execution(head, envp);
}
