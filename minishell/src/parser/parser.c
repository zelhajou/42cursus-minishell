/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:43:46 by zelhajou          #+#    #+#             */
/*   Updated: 2024/02/14 16:53:57 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	display_tokens(t_token *tokens)
{
	t_token	*token;

	token = tokens;
	while (token)
	{
		printf("Token: [ %-20s ]\tType: [ %-20s ]\n",
			token->value, get_token_type_name(token->type));
		token = token->next;
	}
}

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->next = NULL;
	return (token);
}

void	add_token_to_list(t_token **tokens, t_token *new_token)
{
	t_token	*last;

	if (!*tokens)
		*tokens = new_token;
	else
	{
		last = *tokens;
		while (last->next)
			last = last->next;
		last->next = new_token;
	}
}

void	handle_quotes(char **input, t_token **tokens)
{
	char	quote_type;
	char	*start;
	char	*quoted_content;

	quote_type = **input;
	start = ++(*input);
	while (**input && **input != quote_type)
		(*input)++;
	if (*input != start)
	{
		quoted_content = strndup(start, *input - start);
		if (quoted_content)
		{
			add_token_to_list(tokens, new_token(TOKEN_WORD, quoted_content));
			free(quoted_content);
		}
		else
		{
			ft_putstr_fd("Error: Malloc failed in handle_quotes.\n", 2);
			/* error handling */
		}
	}
	if (**input == quote_type)
		(*input)++;
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
	while (**input && !ft_strchr(" \t\n\'\"<>|$", **input))
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
		{
			ft_putstr_fd("Error: Malloc failed in handle_word.\n", 2);
			// errror handling
		}
	}
}

void	handle_environment_variables(char **input, t_token **tokens)
{
	char	*start;
	char	*var_name;

	start = (*input)++;
	while (**input && (ft_isalnum(**input) || **input == '_'))
		(*input)++;
	var_name = strndup(start, *input - start);
	if (var_name)
	{
		add_token_to_list(tokens, new_token(TOKEN_ENV_VAR, var_name));
		free(var_name);
	}
	else
	{
		ft_putstr_fd("Error: Malloc failed in handle env variables.\n", 2);
		// error handling
	}
}

t_token	*tokenize_input(char *input)
{
	t_token	*tokens;

	tokens = NULL;
	while (*input)
	{
		while (*input && ft_strchr(" \t\n", *input))
			input++;
		if (ft_strchr("\'\"", *input))
			handle_quotes(&input, &tokens);
		else if (ft_strchr("><|", *input))
			handle_special_chars(&input, &tokens);
		else if (*input == '$')
			handle_environment_variables(&input, &tokens);
		else
			handle_word(&input, &tokens);
	}
	return (tokens);
}
