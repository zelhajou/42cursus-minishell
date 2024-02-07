#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

typedef struct s_node {
	char *value;
	struct s_node *left;
	struct s_node *right;
} t_node;

t_node *create_node(char *value) {
	t_node *node = (t_node *)malloc(sizeof(t_node));
	node->value = value;
	node->left = NULL;
	node->right = NULL;
	return node;
}


t_node *parseTree(char *input) {
	t_node *root = NULL;
	t_node *current = NULL;
	t_node *parent = NULL;
	int i = 0;
	while (input[i] != '\0') {

	}
	return root;
}

void print_tree(t_node *root) {
	if (root == NULL) {
		return;
	}
	printf("%s\n", root->value);
	print_tree(root->left);
	print_tree(root->right);
}
t_node *multip(char *s);
t_node *plus(char *s)
{
	for (size_t i = 0; s && s[i]; i++)
	{
		if (s[i] == '+' || s[i] == '-')
		{
			t_node *node = create_node(s[i] == '+' ? "+" : "-");
			s[i] = '\0';
			node->left = multip(s);
			node->right = plus(s + i + 1);
			return node;
		}
	}
	return multip(s);
}
t_node *multip(char *s)
{
	for (size_t i = 0; s && s[i]; i++)
	{
		if (s[i] == '*' || s[i] == '/')
		{
			t_node *node = create_node(s[i] == '*' ? "*" : "/");
			s[i] = '\0';
			node->left = multip(s);
			node->right = create_node(s + i + 1);
			return node;
		}
	}
	return create_node((s));
}

int main() {
 	char *input = readline("Calculate: ");

	t_node *root = plus(input);
	print_tree(root);

   
    return 0;
}

