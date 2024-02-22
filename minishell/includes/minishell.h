/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 16:43:38 by zelhajou          #+#    #+#             */
/*   Updated: 2024/02/22 22:38:55 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// System includes
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
// local includes
# include "libft.h"

// Token Structure
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_ENV_VAR,
	TOKEN_EOF,
	TOKEN_TYPE_COUNT
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_ast_node
{
	t_token_type 		type;
	char				**args;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

// Syntax Checker Functions
int			syntax_error_checker(const char *input);
int			has_unclosed_quotes(const char *input);
int			has_invalid_redirections(const char *input);
int			has_misplaced_operators(const char *input);
int			has_logical_operators(const char *input);
// Tokenizer Functions
void		handle_quotes(char **input, t_token **tokens);
void		handle_special_chars(char **input, t_token **tokens);
void		handle_word(char **input, t_token **tokens);
t_token		*tokenize_input(char *input);
// Tokenizer Utils
t_token		*new_token(t_token_type type, char *value);
void		add_token_to_list(t_token **tokens, t_token *new_token);
void		display_tokens(t_token *tokens);
const char	*get_token_type_name(t_token_type type);
void		free_tokens(t_token *tokens);
// Parser Functions
t_ast_node	*parse_tokens(t_token **tokens);
t_ast_node	*parse_command(t_token **tokens);
// Parser Utils
t_ast_node	*new_ast_node(t_token_type type);
void		free_ast(t_ast_node *node);


void generate_ast_diagram(t_ast_node *root);

#endif
