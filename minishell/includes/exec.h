#ifndef	EXEC_H
# define EXEC_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

#define R_F 1
#define W_F 2
#define W_FA 3
#define X_F 4
#define F_R 5

typedef	struct tree
{
	char			*val;
	struct	tree		*right;
	struct	tree		*left;
	struct	tree		*prev;
	int			type;
}		s_tree;

typedef	struct	en
{
	char			**__env;
	char			***env__;
}		s_en;

void		close_pipe(int fd_1, int fd_2);
int		sizeof_str(char *str, char end);
char		*strcopy(char *src);
void		s_strcopy(char *s_1, char *s_2, int st, int en);
int		str_cmp(char *s_1, char *s_2, char *s_3);
void		free_multible(char **arr);
void		free_tree(s_tree *head);
char		*get_file_path(char *file, char **envp, char *env_var, int mode);
char		**generate_cmd_arr(char *cmd, char **envp, int c);
char		*get_var_subpaths(char *env_var, char *file, int *indx_s);
char		*get_next_substr(char *str, char del, int *index);
int		get_string_accurance(char **haystack, char *needle, int n_length);
int		check_path_access(char *path, int mode);
void		increment_path_index(char *env_var, int *indx_s, int *a);
int		get_strs_count(char *str, char del);
void		terminate(s_en *env);
int		is_builtin(char *_cmd);
void		free_env(s_en *env);
int		is_space(char *line);
int		check_line(char **line);
void		ctrl_c_ha(int a);
int		string_to_int(char *str);
int		int_size(int num);

int		echo__(char **_cmd);
int		env_print(char *_cmd, s_en *env, int con);
int		env_modify(char **_cmd, s_en *env);
int		cd__(char **_cmd, s_en *env);

int		get_env_index(s_en *env, char *name);
char		***env_copy(s_en *env, int a, int a_2, int d);
void		env_minus_one(s_en *env, int c);
void		env_plus_one(s_en *env, char *cmd, int b, int con);
char		*current_abs_path(int size, int tries);
char		*expand_it(char *line, s_en *env);
void		env_replace_var(char *var, s_en *env);
void		adapt_status_env(s_en *env, int status, char *start);
void		update_pwd_env(char *new_, s_en *env, int c);
int		change_dir(char *path, s_en *env);

int		__shell_init(s_en *env, char **__env);
void		general_execution(s_tree *head, s_en *env, int *status);
s_tree		*parse_it(char *line, s_en *env);

#endif
