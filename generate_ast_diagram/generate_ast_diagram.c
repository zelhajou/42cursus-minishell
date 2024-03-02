#include "minishell.h"

void print_escaped(FILE *stream, const char *str)
{
    if (!str) return;
    while (*str)
	{
        switch (*str)
		{
            case '\n': fprintf(stream, "\\n"); break;
            case '\"': fprintf(stream, "\\\""); break;
            case '\\': fprintf(stream, "\\\\"); break;
            default: fputc(*str, stream);
        }
        str++;
    }
}

void print_ast_dot(t_ast_node *node, FILE *stream)
{
    if (node == NULL) return;

    fprintf(stream, "\"%p\" [label=\"", (void*)node);
    // Print node type
    switch (node->type)
	{
        // Adjust these labels based on your specific types and what they represent
        case TOKEN_WORD: fprintf(stream, "CMD: "); break;
        case TOKEN_REDIR_IN:
        case TOKEN_REDIR_OUT:
        case TOKEN_REDIR_APPEND:
        case TOKEN_REDIR_HEREDOC: fprintf(stream, "REDIR: "); break;
        case TOKEN_PIPE: fprintf(stream, "|"); break;
        default: fprintf(stream, "UNKNOWN"); break;
    }
    // Print all arguments for the node
    if (node->args)
	{
        for (int i = 0; node->args[i] != NULL; i++)
		{
            if (i > 0) fprintf(stream, " "); // Add space between arguments
            print_escaped(stream, node->args[i]);
        }
    }
    fprintf(stream, "\"];\n");
    if (node->left != NULL)
	{
        fprintf(stream, "\"%p\" -> \"%p\" [label=\"L\"];\n", (void*)node, (void*)node->left);
        print_ast_dot(node->left, stream);
    }
    if (node->right != NULL)
	{
        fprintf(stream, "\"%p\" -> \"%p\" [label=\"R\"];\n", (void*)node, (void*)node->right);
        print_ast_dot(node->right, stream);
    }
}

void generate_ast_diagram(t_ast_node *root)
{
    FILE *stream = fopen("ast.dot", "w");
    if (stream == NULL)
	{
        perror("fopen");
        return;
    }

    fprintf(stream, "digraph AST {\n");
    print_ast_dot(root, stream);
    fprintf(stream, "}\n");
	fclose(stream);
}