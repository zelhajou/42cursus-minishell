/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 21:54:38 by zelhajou          #+#    #+#             */
/*   Updated: 2024/02/22 22:01:44 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_tokens(t_token *tokens)
{
	t_token	*token;

	token = tokens;
	while (token)
	{
		printf("Token: \033[0;36m %-20s \033[0m |\t \
			Type: \033[0;35m %-18s \033[0m \n",
			token->value, get_token_type_name(token->type));
		printf("--------------------------------------------------\n");
		token = token->next;
	}
}

const char	*get_token_type_name(t_token_type type)
{
	const char	*token_type_names[TOKEN_TYPE_COUNT];

	token_type_names[0] = "WORD";
	token_type_names[1] = "PIPE";
	token_type_names[2] = "REDIRECT_IN";
	token_type_names[3] = "REDIRECT_OUT";
	token_type_names[4] = "REDIRECT_APPEND";
	token_type_names[5] = "REDIRECT_HEREDOC";
	token_type_names[6] = "TOKEN_ENV_VAR";
	token_type_names[7] = "EOF";
	if (type >= 0 && type < TOKEN_TYPE_COUNT)
		return (token_type_names[type]);
	return ("UNKNOWN");
}

void print_escaped(FILE *stream, const char *str) {
    if (!str) return;
    while (*str) {
        switch (*str) {
            case '\n': fprintf(stream, "\\n"); break;
            case '\"': fprintf(stream, "\\\""); break;
            case '\\': fprintf(stream, "\\\\"); break;
            default: fputc(*str, stream);
        }
        str++;
    }
}

void print_ast_dot(t_ast_node *node, FILE *stream) {
    if (node == NULL) return;

    fprintf(stream, "\"%p\" [label=\"", (void*)node);
    // Print node type
    switch (node->type) {
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
    if (node->args) {
        for (int i = 0; node->args[i] != NULL; i++) {
            if (i > 0) fprintf(stream, " "); // Add space between arguments
            print_escaped(stream, node->args[i]);
        }
    }
    fprintf(stream, "\"];\n");

    if (node->left != NULL) {
        fprintf(stream, "\"%p\" -> \"%p\" [label=\"L\"];\n", (void*)node, (void*)node->left);
        print_ast_dot(node->left, stream);
    }
    if (node->right != NULL) {
        fprintf(stream, "\"%p\" -> \"%p\" [label=\"R\"];\n", (void*)node, (void*)node->right);
        print_ast_dot(node->right, stream);
    }
}

void generate_ast_diagram(t_ast_node *root) {
    FILE *stream = fopen("ast.dot", "w");
    if (stream == NULL) {
        perror("fopen");
        return;
    }

    fprintf(stream, "digraph AST {\n");
    print_ast_dot(root, stream);
    fprintf(stream, "}\n");

    fclose(stream);
}