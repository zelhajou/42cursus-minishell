/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:26:48 by zelhajou          #+#    #+#             */
/*   Updated: 2024/03/02 04:41:03 by zelhajou         ###   ########.fr       */
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
	int		in_quote;
	char	quote_char;

	start = *input;
	in_quote = 0;
	quote_char = '\0';
	while (**input)
	{
		update_quote_status(**input, &in_quote, &quote_char);
		if (!in_quote && ft_strchr(" \t\n><|", **input))
			break ;
		(*input)++;
	}
	add_word_token_if_valid(&start, input, tokens);
}

t_token	*tokenize_input(char *input)
{
	t_token	*tokens;

	tokens = NULL;
	while (*input)
	{
		while (*input && ft_strchr(" \t\n", *input))
			input++;
		if (ft_strchr("><|", *input))
			handle_special_chars(&input, &tokens);
		else
			handle_word(&input, &tokens);
	}
	return (tokens);
}
