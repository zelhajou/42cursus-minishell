/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 16:43:38 by zelhajou          #+#    #+#             */
/*   Updated: 2024/03/02 20:55:12 by zelhajou         ###   ########.fr       */
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
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}	t_token;

typedef struct s_ast_node
{
	t_token_type		type;
	int					file_type;
	char				**args;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

typedef struct s_env
{
	char				**original_env;
	char				***parsed_env;
}	t_env;

/* ------------------ Main Shell Functionality ------------------ */

void		main_shell_execution_loop(t_env *env);
void		setup_signal_handlers(void);
void		handle_ctrl_c(int sig_num);
void		child_ctrl_c(int sig_num);

/* ------------------ Input Processing ------------------ */

t_token		*process_and_tokenize_input(char *input);
char		*preprocess_input_for_builtins(char *line, t_env *env);

/* ------------------ Syntax Analysis ------------------ */

int			syntax_error_checker(const char *input);
int			has_unclosed_quotes(const char *input);
int			has_invalid_redirections(const char *input);
int			has_misplaced_operators(const char *input);
int			has_logical_operators(const char *input);
void		update_quote_counts(char c, int *s_q_count, int *d_q_count);
const char	*skip_spaces(const char *input);
int			is_invalid_operator(const char **input);
void		update_quote_status(char c, int *in_quote, char *quote_char);
void		add_word_token_if_valid(char **start, char **input,
				t_token **tokens);

/* ------------------ Token Management ------------------ */

t_token		*new_token(t_token_type type, char *value);
void		add_token_to_list(t_token **tokens, t_token *new_token);
void		free_tokens(t_token *tokens);
void		handle_quotes(char **input, t_token **tokens);
void		handle_special_chars(char **input, t_token **tokens);
void		handle_word(char **input, t_token **tokens);
t_token		*tokenize_input(char *input);

/* ------------------ AST Construction and Management ------------------ */

t_ast_node	*new_ast_node(t_token_type type);
void		free_ast(t_ast_node *node);
t_ast_node	*parse_tokens(t_token **tokens);
t_ast_node	*parse_command(t_token **tokens);
int			count_command_arguments(t_token *current);
void		fill_command_arguments(t_ast_node *command_node,
				t_token **tokens, int arg_count);
t_ast_node	*parse_pipeline(t_token **tokens);
t_ast_node	*parse_redirection(t_token **tokens);
t_ast_node	*create_file_node(t_token *token);
t_ast_node	*create_and_link_redirection(t_token **tokens, t_token *tmp);

/* ------------------ Built-in Command Execution ------------------ */

int			cd_cmd(char **cmd, t_env *env, int *out_fd);
int			echo_cmd(char **cmd, int *out_fd);
int			env_or_pwd_cmd(char *cmd, t_env *env, int condition, int *out_fd);
char		**export_cmd(char **cmd, t_env *env, int *out_fd, int **status);
char		**unset_or_export_cmd(char **cmd, t_env *env,
				int *out_fd, int *status);

/* ------------------ Built-in Command Utilities ------------------ */

void		set_new_pwd_in_env(char *new_path, t_env *env, int unused);
int			change_current_directory(char *path, t_env *env);
char		*get_current_working_directory(int size, int tries, int fd);

/* ------------------ Input Validation and Environment Management -------- */

int			check_line(char **line);
int			find_env_var_index(t_env *env, char *name);
void		free_environment_variables(t_env *env);
void		replace_env_var(char *var, t_env *env);
void		append_env_var(char *var, t_env *env);
int			is_string_numeric(char *s_1);

/* ------------------ Printing and Utility Functions ------------------ */

void		print_env_var_to_fd(char *key, char *value, int fd);
void		print_export_declaration_to_fd(char *key, char *value, int fd);

/* ------------------ Command Execution Management ------------------ */

void		adjust_ast_nodes_for_execution(t_ast_node *head);
void		command_execution_manager(t_ast_node *head,
				t_env *env, int *status);
int			execute_ast_node(t_ast_node *head, int *piped, t_env *env);
int			prepare_and_execute_command(char **cmd, int *fd,
				int *piped, t_env *env);
int			handle_command_redirection(t_ast_node *head, int *piped,
				t_env *env, int *fd);
int			handle_piped_command_execution(t_ast_node *head,
				int *piped, t_env *env, int *fd);
int			exec_here_doc(char *limiter, int *piped, int *fd);
void		initialize_or_reset_pipe_state(int *piped, int flag);
int			open_file_for_redirection(t_ast_node *head, int *piped);
int			check_if_command_is_builtin(char *cmd);
int			manage_builtin_execution(char **cmd, int *fd,
				t_env *env, int *piped);
int			manage_single_builtin_execution(char **cmd, int *fd,
				t_env *env, int *piped);
int			execute_builtin_command_in_child(char **cmd,
				t_env *env, int *out_fd);

/* ----------- Path and Environment Variable Handling --------- */

void		increment_path_index(char *env_var, int *index_start,
				int *index_end);
void		add_env_entry(t_env *env, char *cmd,
				int bool_condition, int condition);
void		remove_env_entry(t_env *env, int index);
void		update_env_status(t_env *env, int status, char *start);
int			is_path_accessible(char *path, int mode);
int			env_just_print(t_env *env, int con, int *_out_fd);

/* ------------------ String Manipulation and Checking ------------------ */

void		s_strcopy(char *dest, char *src, int start, int end);
char		*strcopy(char *src);
char		*str_without_char(char *str, char delimiter);
char		*remove_quotes_from_str(char *str);
int			str_cmp(char *str1, char *str2, char *str3);
int			is_space(char *line);
int			sizeof_str(char *str, char delimiter);
int			count_strings_in_array(char **arr);

/* ------------------ Process and Pipeline Management ------------------ */

int			wait_for_children(int status, int *piped);
void		count_redirections_and_pipes(t_ast_node *head, int *piped);
void		close_pipe_ends(int fd_1, int fd_2);
void		child_fds_managment(int *_piped, int *_fd, int *fd_);
void		parent_fds_managment(int *_piped, int *_fd, int *fd_);

/* ------------------ Variable Expansion and Replacement ------------------ */

void		expand_variables_in_ast(t_ast_node *head, t_env *env);
char		*recursively_expand_variables(char *var, t_env *env);
char		*replace_variable_with_value(char *old_var, char *new_value,
				int start, int end);

/* ------------------ Advanced String and Array Operations ------------------ */

char		**merge_command_args(char **first_args, char **additional_args);
char		***duplicate_env_structure(t_env *env, int a, int a_2, int d);
int			count_substrings(char *str, char delimiter);
int			find_substr_index(char **haystack, char *needle, int needle_length);
char		*find_next_substring(char *str, char delimiter, int *index);
int			string_to_int(char *str);
int			is_valid_variable_start(char *str, int index, int check_dollar);
void		free_string_array(char **arr);
char		*fetch_file_path(char *file, char **envp, char *env_var, int mode);
char		*create_subpath_from_var(char *env_var, char *file,
				int *index_start);

/* ------------------ Miscellaneous Utilities ------------------ */

int			initialize_shell_with_environment(t_env *env, char **original_env);
void		cleanup_and_exit_shell(t_env *env, int status);
int			get_shell_exit_status(int error_code);
int			count_digits_in_int(int num);
char		**prepare_cmd_arguments(char *cmd, char **envp, int condition);
int			verify_command_file_permissions(t_ast_node *head, char **env);

void		generate_ast_diagram(t_ast_node *root);
void		display_tokens(t_token *tokens);

#endif
