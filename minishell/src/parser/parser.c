/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:43:46 by zelhajou          #+#    #+#             */
/*   Updated: 2024/02/22 22:28:19 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

t_ast_node	*parse_command(t_token **tokens)
{
	t_ast_node	*command_node;
	t_token		*current;
	t_token		*tmp;
	int			arg_count;
	int			i;

	command_node = new_ast_node(TOKEN_WORD);
	current = *tokens;
	arg_count = 0;
	i = 0;
	while (current && current->type == TOKEN_WORD)
	{
		arg_count++;
		current = current->next;
	}
	command_node->args = malloc(sizeof(char *) * (arg_count + 1));

	while (i < arg_count)
	{
		command_node->args[i] = strdup((*tokens)->value);
		tmp = *tokens;
		*tokens = (*tokens)->next;
		free((tmp)->value);
		free((tmp));
		i++;
	}
	command_node->args[arg_count] = NULL;
	return (command_node);
}

t_ast_node *new_ast_file(t_token *token) {
    t_ast_node *node = malloc(sizeof(t_ast_node));
    if (!node) return NULL;
    node->type = token->type;
    node->args = malloc(sizeof(char *) * 2);
    if (!node->args) {
        free(node);
        return NULL;
    }
    node->args[0] = token->value;
    node->args[1] = NULL;
    node->left = NULL;
    node->right = NULL;
	free(token);
    return node;
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
	{
		redirect_node = new_ast_node((*tokens)->type);
		(*tokens) = (*tokens)->next->next;
		redirect_node->left = parse_redirection(tokens);
		redirect_node->right = new_ast_file(((tmp)->next));
		free((tmp)->value);
		free(tmp);
		return (redirect_node);
	}
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
			free(next_token->value);
			free(next_token);
			return (redirect_node);
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
			pipe_node->right =  parse_pipeline(&(next_token->next));
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
