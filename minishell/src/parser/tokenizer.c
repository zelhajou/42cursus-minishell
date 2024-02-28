/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:26:48 by zelhajou          #+#    #+#             */
/*   Updated: 2024/02/28 22:29:18 by beddinao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quotes(char **input, t_token **tokens)
{
	char	quote_type;
	char	*start;
	char	*quoted_content;

	quote_type = **input;
	start = *input;
	(*input)++;
	while (**input && **input != quote_type)
		(*input)++;
	if (**input == quote_type)
	{
		quoted_content = strndup(start, (*input - start) + 1);
		if (quoted_content)
		{
			add_token_to_list(tokens, new_token(TOKEN_WORD, quoted_content));
			free(quoted_content);
		}
		else
			ft_putstr_fd("Error: Malloc failed in handle_quotes.\n", 2);
		(*input)++;
	}
}

void	handle_special_chars(char **input, t_token **tokens)
{
	if (**input == '>')
	{
		if (*(*input + 1) == '>')
		{
			add_token_to_list(tokens, new_token(TOKEN_REDIR_APPEND, ">>"));
			(*input)++;
		}
		else
			add_token_to_list(tokens, new_token(TOKEN_REDIR_OUT, ">"));
	}
	else if (**input == '<')
	{
		if (*(*input + 1) == '<')
		{
			add_token_to_list(tokens, new_token(TOKEN_REDIR_HEREDOC, "<<"));
			(*input)++;
		}
		else
			add_token_to_list(tokens, new_token(TOKEN_REDIR_IN, "<"));
	}
	else if (**input == '|')
		add_token_to_list(tokens, new_token(TOKEN_PIPE, "|"));
	(*input)++;
}

void	handle_word(char **input, t_token **tokens)
{
	char	*start;
	char	*word;

	start = *input;
	while (**input && !ft_strchr(" \t\n<>|", **input))
		(*input)++;
	if (*input > start)
	{
		word = strndup(start, *input - start);
		if (word)
		{
			add_token_to_list(tokens, new_token(TOKEN_WORD, word));
			free(word);
		}
		else
			ft_putstr_fd("Error: Malloc failed in handle_word.\n", 2);
	}
}

// void	handle_environment_variables(char **input, t_token **tokens)
// {
// 	char	*start;
// 	char	*var_name;

// 	start = (*input)++;
// 	while (**input && (ft_isalnum(**input) || **input == '_'))
// 		(*input)++;
// 	var_name = strndup(start, *input - start);
// 	if (var_name)
// 	{
// 		add_token_to_list(tokens, new_token(TOKEN_ENV_VAR, var_name));
// 		free(var_name);
// 	}
// 	else
// 		ft_putstr_fd("Error: Malloc failed in handle env variables.\n", 2);
// }

t_token	*tokenize_input(char *input)
{
	t_token	*tokens;

	tokens = NULL;
	while (*input)
	{
		while (*input && ft_strchr(" \t\n", *input))
			input++;
		/*if (ft_strchr("\'\"", *input))
			handle_quotes(&input, &tokens);
		else */if (ft_strchr("><|", *input))
			handle_special_chars(&input, &tokens);
		else
			handle_word(&input, &tokens);
	}
	return (tokens);
}
