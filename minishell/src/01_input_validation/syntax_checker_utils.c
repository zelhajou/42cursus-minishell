/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 00:15:54 by zelhajou          #+#    #+#             */
/*   Updated: 2024/03/02 04:44:52 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_quote_counts(char c, int *s_q_count, int *d_q_count)
{
	if (c == 34)
		(*d_q_count)++;
	else if (c == 39)
		(*s_q_count)++;
}

const char	*skip_spaces(const char *input)
{
	while (*input && (*input == ' ' || *input == '\t'))
		input++;
	return (input);
}

int	is_invalid_operator(const char **input)
{
	const char	*operator_start;

	operator_start = *input;
	(*input)++;
	if (*operator_start == **input)
		(*input)++;
	*input = skip_spaces(*input);
	if (**input == '\0' || **input == '>'
		|| **input == '<' || **input == '|')
		return (1);
	return (0);
}

void	update_quote_status(char c, int *in_quote, char *quote_char)
{
	if (!*in_quote && (c == '\'' || c == '\"'))
	{
		*in_quote = 1;
		*quote_char = c;
	}
	else if (*in_quote && c == *quote_char)
		*in_quote = 0;
}

void	add_word_token_if_valid(char **start, char **input, t_token **tokens)
{
	char	*word;

	if (*input > *start)
	{
		word = ft_strndup(*start, *input - *start);
		if (word)
		{
			add_token_to_list(tokens, new_token(TOKEN_WORD, word));
			free(word);
		}
		else
			ft_putstr_fd("Error: Malloc failed in handle_word.\n", 2);
	}
}
