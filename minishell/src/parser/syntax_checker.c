/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:56:51 by zelhajou          #+#    #+#             */
/*   Updated: 2024/02/14 22:03:20 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_quotes(const char *input)
{
	int	i;
	int	s_quote;
	int	d_quote;

	i = -1;
	s_quote = 0;
	d_quote = 0;
	while (input[++i])
	{
		if (input[i] == '\'' && !d_quote)
			s_quote = !s_quote;
		else if (input[i] == '"' && !s_quote)
			d_quote = !d_quote;
	}
	if (s_quote || d_quote)
		return (1);
	return (0);
}

int	check_redir_pipe(const char *input)
{
	int	i;
	int	cmd_found;

	i = 0;
	cmd_found = 0;
	while (input[i])
	{
		if (input[i] == '|' && (i == 0 || input[i + 1] == '\0' || input[i + 1] == '|'))
			return (1);
		if ((input[i] == '<' || input[i] == '>') && input[i + 1] == '\0')
			return (1);
		if (!isspace(input[i]) && input[i] != '|' && input[i] != '<' && input[i] != '>')
			cmd_found = 1;
		i++;
	}
	return (cmd_found ? 0 : 1);
}

int	syntax_error_checker(const char *input)
{
	if (check_quotes(input) || check_redir_pipe(input))
	{
		ft_putstr_fd("Syntax error\n", 2);
		return (1);
	}
	return (0);
}
