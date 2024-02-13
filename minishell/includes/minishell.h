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

typedef  struct  tree
{
  char          *val;
  struct tree    *right;
  struct tree    *left;
  struct tree    *prev;
  int            type;
}

              //// // // executer functions
/// / general_utils
void      close_fd(int fd1, int fd2);
int    sizeof_str(char *str, char end);
char  *strcopy(char *src);
int    str_cmp(char *s_1, char *s_2, char *s_3);
int    is_red(char *str);

// // cmd_formation
char  *get_var_subpaths(char *env_var, char *file, int *indx_s);
char  *get_file_path(char *file, char **envp, char *env_var, int mode);
char  *get_next_substr(char *str, char del, int *index);
char  **generate_cmd_arr(char *cmd, char **envp, int c);
int    get_string_accurance(char **haystack, char *needle, int n_length);
int    check_path_access(char *path, int mode);
void      increment_path_index(char *env_var, int *indx_s, int *a);
int    get_strs_count(char *str, char del);

// /// exec_utils
void      _standards_init(s_tree *head, int *_fd, int *_piped);
void      _standards_out(s_tree *head, int *_fd, int *_piped);
void      __pipes_count(s_tree *head, int *_piped);
void      __in_redirection_count(s_tree *head, int *_piped);
void      __out_redirection_count(s_tree *head, int *_piped);

/// // exec_init
void      open_next_output(s_tree *head, int _out_index, int *_piped, int *_fd);
void      open_next_input(s_tree *head, int _in_index, int *_piped, int *_fd);
void      __adapt_nodes_types(s_tree *head);

/// /// executer
void      exec_one(char **_cmd, int *_fd, char **env, int *_piped);
int    exec_command(char *_cmd_, int *_fd, int *_piped, char **env);
int    execute(s_tree *head, char **env, int *_fd, int *_piped);
int    general_execution(s_tree *head, char **env);


#endif
