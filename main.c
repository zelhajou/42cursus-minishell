#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

typedef struct s_node {

	int value;
	struct s_node *left;
	struct s_node *right;
} t_node;

t_node *create_node(int value) {
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
	printf("%d\n", root->value);
	print_tree(root->left);
	print_tree(root->right);
}


int main() {
 	char *input = readline("Calculate: ");

	t_node *root = parseTree(input);
	print_tree(root);
	// t_node* n1 = create_node(10);
	// t_node* n2 = create_node(20);
	// t_node* n3 = create_node(30);
	// t_node* n4 = create_node(40);
	// t_node* n5 = create_node(50);



	// n1->left = n2;
	// n1->right = n3;
	// n2->left = n4;
	// n2->right = n5;

	// print_tree(n1);

   
    return 0;
}

