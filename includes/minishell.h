/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 20:29:19 by soemin            #+#    #+#             */
/*   Updated: 2026/01/04 17:02:38 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

typedef struct s_list_cmds
{
	int	heredoc_fd;
	int	bltin;
	char	*file_toappend;
	char	*file_toread;
	char	**all_eof;
	char	*eof;
	char	**args;
}	t_list_cmds;

// Global Variable for received signal
extern volatile sig_atomic_t g_signal;
// FUNCTIONS

// parser
t_list_cmds     *cmd_parse(char *line, char *delim, int *count);
int	prepare_cmds(t_list_cmds **cmds, char *line, char **envp, int **cnt_lst);

char	*ft_strtok(char *str, const char *delim);
char	*expand_dollar(const char *line, char **envp, int last_status);
int	unquoted(char **tok, char *buf);
char    *handle_single_quotes(const char *line, int i, char *tok);
char    *handle_double_quotes(const char *line, int i, char **envp, int last_status);
int	append_char(char **tok, char c);
int	append_str(char **tok, size_t *len, const char *s);
char    *unpack_token(char *line, char **envp, int last_status);

// parser utils
void		parse_path(t_list_cmds *cmds, char **envp, int count);
void		*ft_realloc(void *ptr, size_t old_size, size_t new_size);
void            free_all(t_list_cmds *cmds, int count);
char		*next_token(char *str, char *delim);
void		cleanup_cmd(t_list_cmds *cmds, int cmd_count);
void    	check_builtin(t_list_cmds *cmd, int cmd_count);

// redir
int	rephrase_cmd(t_list_cmds *all_cmd, int count, char **envp, int last_status);
int	prepare_redir_append(t_list_cmds *full_cmd);
void	prepare_redir(t_list_cmds *full_cmd);
void	prepare_inredir(t_list_cmds *full_cmd);
int	prepare_heredoc(t_list_cmds *full_cmd);
int	construct_cmd(t_list_cmds *full_cmd);
int	construct_cmd1(t_list_cmds *full_cmd);
void	update_chosen_heredoc(t_list_cmds *full_cmd);
void	handle_one_heredoc(t_list_cmds *full_cmd, int count);

void	free_arg(char **arg);

// redir utils
void	update_infile(t_list_cmds *full_cmd, char *file_name, int count);
int     get_cmdlet_count(char **cmd_arr);
int     is_redir_char(char *arg);
int     is_append_char(char *arg);
int     is_inredirect_char(char *arg);
int     is_heredoc_char(char *arg);

// file
int	handle_file(char *file_name, int is_last);
int	check_file_inredir(char *file_name);

// exec
int     exec_cmds(t_list_cmds *cmds, int count,
		int (*func_ptr)(int*, int*, int*));
int	exec_and_get_status(t_list_cmds *cmds, int cmd_count);
int	run_binary(char **args, char **envp);
int	read_heredoc(char *eof, char **envp, int last_status);
// built-in cmds
int		ft_echo(char **args);
int		ft_pwd(void);
int		ft_env(char **args, char **envp);
int		count_args(char **args);
char	*get_env_var(char **env, const char *name);
void	set_env_var(char **env, const char *name, const char *value);
int		ft_cd(char **args, char **envp);
int		parse_sign(const char *str, int *sign, int *valid);
long	atol_valid(const char *str, int *valid);
int		ft_exit(char **args, int last_status);
int		ft_export(char **args, char ***envp, int *last_status);
int		ft_unset(char **args, char ***envp);
int		run_builtin(char **args, char ***envp, int last_status);
// utils
char	**dup_env(char **envp);
char	*get_path_value(char **envp);
int		ft_setenv(char ***envp, const char *name, const char *value);
void	setup_signals(void);

//error
int	redir_error(void);


#endif
