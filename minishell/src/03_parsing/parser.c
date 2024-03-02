/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:43:46 by zelhajou          #+#    #+#             */
/*   Updated: 2024/03/02 04:23:19 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*parse_command(t_token **tokens)
{
	t_ast_node		*command_node;
	int				arg_count;

	command_node = new_ast_node(TOKEN_WORD);
	arg_count = count_command_arguments(*tokens);
	command_node->args = malloc(sizeof(char *) * (arg_count + 1));
	fill_command_arguments(command_node, tokens, arg_count);
	return (command_node);
}

t_ast_node	*new_ast_file(t_token *token)
{
	t_ast_node			*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = token->type;
	node->args = malloc(sizeof(char *) * 2);
	if (!node->args)
	{
		free(node);
		return (NULL);
	}
	node->args[0] = token->value;
	node->args[1] = NULL;
	node->left = NULL;
	node->right = NULL;
	free(token);
	return (node);
}

t_ast_node	*parse_redirection(t_token **tokens)
{
	t_token		*tmp;
	t_ast_node	*redirect_node;
	t_token		*next_token;

	if (!*tokens)
		return (NULL);
	tmp = *tokens;
	if ((*tokens)->type >= TOKEN_REDIR_IN
		&& (*tokens)->type <= TOKEN_REDIR_HEREDOC)
		return (create_and_link_redirection(tokens, tmp));
	while (*tokens && (*tokens)->next)
	{
		next_token = (*tokens)->next;
		if ((*tokens)->next->type >= TOKEN_REDIR_IN
			&& (*tokens)->next->type <= TOKEN_REDIR_HEREDOC)
		{
			redirect_node = new_ast_node((*tokens)->next->type);
			(*tokens)->next = next_token->next->next;
			redirect_node->left = parse_redirection(&tmp);
			redirect_node->right = new_ast_file((next_token->next));
			return (free(next_token->value), free(next_token), redirect_node);
		}
		*tokens = next_token;
	}
	return (parse_command(&tmp));
}

t_ast_node	*parse_pipeline(t_token **tokens)
{
	t_token		*tmp;
	t_token		*next_token;
	t_ast_node	*pipe_node;

	tmp = *tokens;
	while (*tokens && (*tokens)->next)
	{
		next_token = (*tokens)->next;
		if ((*tokens)->next->type == TOKEN_PIPE)
		{
			pipe_node = new_ast_node((*tokens)->next->type);
			(*tokens)->next = NULL;
			pipe_node->left = parse_redirection(&tmp);
			pipe_node->right = parse_pipeline(&(next_token->next));
			free(next_token->value);
			free(next_token);
			return (pipe_node);
		}
		*tokens = next_token;
	}
	return (parse_redirection(&tmp));
}

t_ast_node	*parse_tokens(t_token **tokens)
{
	if (!tokens || !*tokens)
		return (NULL);
	return (parse_pipeline(tokens));
}
