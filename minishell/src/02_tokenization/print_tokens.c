/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:47:19 by zelhajou          #+#    #+#             */
/*   Updated: 2024/03/05 16:10:18 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// const char	*get_token_type_name(t_token_type type)
// {
// 	const char	*token_type_names[7];

// 	token_type_names[0] = "WORD";
// 	token_type_names[1] = "PIPE";
// 	token_type_names[2] = "REDIRECT_IN";
// 	token_type_names[3] = "REDIRECT_OUT";
// 	token_type_names[4] = "REDIRECT_APPEND";
// 	token_type_names[5] = "REDIRECT_HEREDOC";
// 	token_type_names[6] = "TOKEN_ENV_VAR";
// 	if (type >= 0 && type < 7)
// 		return (token_type_names[type]);
// 	return ("UNKNOWN");
// }

// void	display_tokens(t_token *tokens)
// {
// 	t_token	*token;

// 	token = tokens;
// 	while (token)
// 	{
// 		printf("Token: \033[0;36m %-20s \033[0m |\t \
// 			Type: \033[0;35m %-18s \033[0m \n",
// 			token->value, get_token_type_name(token->type));
// 		printf("--------------------------------------------------\n");
// 		token = token->next;
// 	}
// }