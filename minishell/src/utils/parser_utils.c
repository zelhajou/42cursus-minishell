/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 23:26:44 by zelhajou          #+#    #+#             */
/*   Updated: 2024/02/20 16:37:06 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node *new_ast_node(t_token_type type)
{
    t_ast_node *node;
	
	node = malloc(sizeof(t_ast_node));
    if (!node)
		return (NULL);
    node->type = type;
    node->args = NULL;
    node->left = NULL;
    node->right = NULL;
    return (node);
}

void free_ast(t_ast_node *node)
{
	int i;

	i = 0;
	if (!node)
		return;
	if (node->type == TOKEN_WORD && node->args)
	{
		while (node->args && node->args[i])
		{
			free(node->args[i]);
			i++;
		}
        free(node->args);
    }
    free_ast(node->left);
    free_ast(node->right);
    free(node);
}
