#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <readline/readline.h>
#include <readline/history.h>

#include <fcntl.h>
#include <sys/wait.h>

#include "libft.h"


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


// Syntax Checker Functions
int	check_unclosed_quotes(const char *input);
int check_redirections_and_pipes_syntax(const char *input);
int syntax_error_checker(const char *input);

// Token Functions
t_token *new_token(t_token_type type, char *value);
void add_token_to_list(t_token **tokens, t_token *new_token);
void handle_quotes(char **input, t_token **tokens);
void handle_special_chars(char **input, t_token **tokens);
void handle_word(char **input, t_token **tokens);
t_token *tokenize_input(char *input);
void display_tokens(t_token *tokens);





#endif
