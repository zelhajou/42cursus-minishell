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

# define R_F 10
# define W_F 20
# define W_FA 30
# define X_F 40
# define F_R 50
# define B_FILE_ERR(errn) ((errn == 2) \
	       	? (127) : ((errn == 13) \
			? (126) : (errn)))

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# include "../lib/libft/libft.h"

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
	int			file_type;
	char			**args;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}		t_ast_node;

typedef	struct	en
{
	char			**__env;
	char			***env__;
}		s_en;

// Syntax Checker Functions

int				syntax_error_checker(const char *input);
int				has_unclosed_quotes(const char *input);
int				has_invalid_redirections(const char *input);
int				has_misplaced_operators(const char *input);
int				has_logical_operators(const char *input);

// Tokenizer Functions

void			handle_quotes(char **input, t_token **tokens);
void			handle_special_chars(char **input, t_token **tokens);
void			handle_word(char **input, t_token **tokens);
t_token			*tokenize_input(char *input);

// Tokenizer Utils

t_token			*new_token(t_token_type type, char *value);
void			add_token_to_list(t_token **tokens, t_token *new_token);
void			display_tokens(t_token *tokens);
const char		*get_token_type_name(t_token_type type);
void			free_tokens(t_token *tokens);

// Parser Functions

t_ast_node		*parse_tokens(t_token **tokens);
t_ast_node		*parse_command(t_token **tokens);

// Parser Utils

t_ast_node		*new_ast_node(t_token_type type);
void			free_ast(t_ast_node *node);
void			generate_ast_diagram(t_ast_node *root);

/// // /// Execution

void			close_pipe(int fd_1, int fd_2);
int			sizeof_str(char *str, char end);
int			sizeof_arr(char **arr);
char			*strcopy(char *src);
void			s_strcopy(char *s_1, char *s_2, int st, int en);
int			str_cmp(char *s_1, char *s_2, char *s_3);
void			free_multible(char **arr);
char			*get_file_path(char *file, char **envp, char *env_var, int mode);
char			**generate_cmd_arr(char *cmd, char **envp, int c);
char			*get_var_subpaths(char *env_var, char *file, int *indx_s);
char			*get_next_substr(char *str, char del, int *index);
int			get_string_accurance(char **haystack, char *needle, int n_length);
int			check_path_access(char *path, int mode);
void			increment_path_index(char *env_var, int *indx_s, int *a);
int			get_strs_count(char *str, char del);
void			terminate(s_en *env);
int			is_builtin(char *_cmd);
void			free_env(s_en *env);
int			is_space(char *line);
int			check_line(char **line);
void			ctrl_c_ha(int a);
void			ctrl_q_ha(int a);
int			string_to_int(char *str);
int			int_size(int num);
void			env_print_fd(char *str_1, char *str_2, int fd);
void			export_print_fd(char *str_1, char *str_2, int fd);

int		echo__(char **_cmd, int *_out_fd);
int		env_print(char *_cmd, s_en *env, int con, int *_out_fd);
char		**env_modify(char **_cmd, s_en *env, int *_out_fd, int *s);
int		cd__(char **_cmd, s_en *env, int *_out_fd);

int		get_env_index(s_en *env, char *name);
char		***env_copy(s_en *env, int a, int a_2, int d);
void		env_minus_one(s_en *env, int c);
void		env_plus_one(s_en *env, char *cmd, int b, int con);
char		*current_abs_path(int size, int tries, int fd);
void		_expand_it(t_ast_node *head, s_en *env);
void		env_replace_var(char *var, s_en *env);
void		adapt_status_env(s_en *env, int status, char *start);
void		update_pwd_env(char *new_, s_en *env, int c);
int		change_dir(char *path, s_en *env);
void		child_fds_managment(int *_piped, int *_fd, int *fd_);
void		parent_fds_managment(int *_piped, int *_fd, int *fd_);
void		_piped_init(int *_piped, int f);
void		open_file(t_ast_node *head, int *_piped);
int		builtins_child(char **_cmd_, s_en *env, int *_out_fd);
char		**merge_it(char **f_args, char **_cmd_);
char		*ex_statment_misdefinition(char *line);

int		exec_command(char **_cmd_, int *_fd, int *_piped, s_en *env);
int		exec_built_ins(char **_cmd_, int *_fd, s_en *env, int *_piped);

int		execute_pipe(t_ast_node *head, int *_piped, s_en *env, int *_fd);
int		execute_redirection(t_ast_node *head, int *_piped, s_en *env, int *_fd);
int		execution_circle(t_ast_node *head, int *_piped, s_en *env);

int		__files_permission(t_ast_node *head, char **env);
void		__adapt_nodes(t_ast_node *head);
void		__redirection_count(t_ast_node *head, int *_piped);

int		__shell_init(s_en *env, char **__env);
void		general_execution(t_ast_node *head, s_en *env, int *status);

#endif
