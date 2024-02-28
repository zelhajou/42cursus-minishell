/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 16:43:38 by zelhajou          #+#    #+#             */
/*   Updated: 2024/02/28 17:34:35 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define READ_FILE 10
# define READ_FROM_APPEND 15
# define WRITE_FILE 20
# define WRITE_FILE_APPEND 30
# define EXECUTE_FILE 40
# define FILE_READY 50

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "../lib/get_next_line/get_next_line.h"

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_ENV_VAR,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_ast_node
{
	t_token_type		type;
	int					file_type;
	char				**args;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}		t_ast_node;

typedef struct s_env
{
	char			**original_env;
	char			***parsed_env;
}		t_env;

// main functions
void			main_shell_execution_loop(t_env *env);

// Preprocessor Functions
t_token			*process_and_tokenize_input(char *input);
char			*preprocess_input_for_builtins(char *line, t_env *env);

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

// Builtins
int				cd_cmd(char **_cmd, t_env *env, int *_out_fd);
int				echo_cmd(char **_cmd, int *_out_fd);
int				env_or_pwd_cmd(char *_cmd, t_env *env, int con, int *_out_fd);
char			**export_cmd(char **_cmd, t_env *env, int *_out_fd, int **s);
char			**unset_or_export_cmd(char **_cmd, t_env *env, int *_out_fd, int *s);

// Builtins Utils
void			set_new_pwd_in_env(char *new_, t_env *env, int c);
int				change_current_directory(char *path, t_env *env);
char			*get_current_working_directory(int size, int tries, int fd);
void			print_env_var_to_fd(char *str_1, char *str_2, int fd);
void			print_export_declaration_to_fd(char *str_1, char *str_2, int fd);

// Execution Manager
void			command_execution_manager(t_ast_node *head, t_env *env, int *status);
int				execute_ast_node(t_ast_node *head, int *_piped, t_env *env);
int				handle_command_redirection(t_ast_node *head, int *_piped, t_env *env, int *_fd);
int				handle_piped_command_execution(t_ast_node *head, int *_piped, t_env *env, int *_fd);

// Signal Handlers
void			setup_signal_handlers(void);
void			handle_ctrl_c(int a);



// Execution
void			close_pipe_ends(int fd_1, int fd_2);
void			s_strcopy(char *s_1, char *s_2, int st, int en);
void			free_string_array(char **arr);
void			increment_path_index(char *env_var, int *indx_s, int *a);
void			remove_env_entry(t_env *env, int c);
void			add_env_entry(t_env *env, char *cmd, int b, int con);
void			update_env_status(t_env *env, int status, char *start);
void			child_fds_managment(int *_piped, int *_fd, int *fd_);
void			parent_fds_managment(int *_piped, int *_fd, int *fd_);
char			**unset_or_export_cmd(char **_cmd, t_env *env, int *_out_fd, int *s);
char			*strcopy(char *src);
char			**merge_command_args(char **f_args, char **_cmd_);
char			*str_without_char(char *str, char del);
char			***duplicate_env_structure(t_env *env, int a, int a_2, int d);
char			*remove_quotes_from_str(char *str);
int				sizeof_str(char *str, char end);
int				count_strings_in_array(char **arr);
int				is_path_accessible(char *path, int mode);
int				str_cmp(char *s_1, char *s_2, char *s_3);
int				is_space(char *line);
int				check_line(char **line);
int				find_env_var_index(t_env *env, char *name);
int				string_to_int(char *str);
void			exec_here_doc(char *limiter, int *_piped, int *_fd);
void			initialize_or_reset_pipe_state(int *_piped, int f);
void			open_file_for_redirection(t_ast_node *head, int *_piped);
int				check_if_command_is_builtin(char *_cmd);
int				execute_builtin_command_in_child(char **_cmd_, t_env *env, int *_out_fd);
int				wait_for_children(int status, int *_piped);
void			count_redirections_and_pipes(t_ast_node *head, int *_piped);
void			adjust_ast_nodes_for_execution(t_ast_node *head);
int				verify_command_file_permissions(t_ast_node *head, char **env);
void			expand_variables_in_ast(t_ast_node *head, t_env *env);
char			*recursively_expand_variables(char *var, t_env *env);
char			*replace_variable_with_value(char *old_var, char *__new, int st, int end);
int				is_valid_variable_start(char *str, int index, int con);
int				prepare_and_execute_command(char **_cmd_, int *_fd, int *_piped, t_env *env);
int				initialize_shell_with_environment(t_env *env, char **original_env);
void			free_environment_variables(t_env *env);
void			cleanup_and_exit_shell(t_env *env, int status);
int				manage_builtin_execution(char **_cmd_, int *_fd, t_env *env, int *_piped);
int				get_shell_exit_status(int err);
int				count_digits_in_int(int num);
void			replace_env_var(char *var, t_env *env);
void			append_env_var(char *var, t_env *env);
char			**prepare_cmd_arguments(char *cmd, char **envp, int c);
char			*find_next_substring(char *str, char del, int *index);
char			*fetch_file_path(char *file, char **envp, char *env_var, int mode);
char			*create_subpath_from_var(char *env_var, char *file, int *indx_s);
int				find_substr_index(char **haystack, char *needle, int n_length);
int				count_substrings(char *str, char del);
int				is_valid_variable_start(char *str, int index, int con);

#endif
