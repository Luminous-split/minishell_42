/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 20:29:19 by soemin            #+#    #+#             */
/*   Updated: 2026/01/16 13:14:28 by ksan             ###   ########.sg       */
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
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

typedef struct s_list_cmds
{
	int		heredoc_fd;
	int		bltin;
	int		f_in;
	int		*hd_canceled;
	char	*f_out;
	char	*file_toappend;
	char	*file_toread;
	char	**all_eof;
	char	*eof;
	char	**args;
}	t_list_cmds;

// Global Variable for received signal
extern volatile sig_atomic_t	g_signal;
// FUNCTIONS

// parser
int			prepare_cmds(t_list_cmds **cmds, char *line,
				char **ep, int *vars);
int			unquoted(char **tok, char *buf);
int			append_char(char **tok, char c);
int			append_str(char **tok, const char *s);
int			append_nstr(char **tok, const char *s, size_t n);
char		*ft_strtok(char *str, const char *delim);
char		*handle_single_quotes(const char *line, int start, char *tok);
char		*handle_double_quotes(const char *line,
				int start, char **ep, int last_status);
int			handle_dollar(char **tok,
				const char *line, char **envp, int last_status);
char		*expand_dollar(const char *line, char **ep, int last_status);
char		*unpack_token(char *line, char **envp, int last_status);
t_list_cmds	*cmd_parse(char *line, char *delim, int *count, int *fl);

// parser utils
int			check_pending(char *line);
int			is_invalid_line(char *line);
void		handle_pending_pipe(char **line);
void		parse_path(t_list_cmds *cmds, char **ep, int count);
void		*ft_realloc(void *ptr, size_t old_size, size_t new_size);
void		free_all(t_list_cmds *cmds, int count);
char		**split_line(char const *s, char c);
char		**ft_insert_words(char **splitted, char const *s, char c);
char		*next_token(char *str, char *delim);
void		cleanup_cmd(t_list_cmds *cmds, int cmd_count);
void		check_builtin(t_list_cmds *cmd, int cmd_count);

// redir
int			rephrase_cmd(t_list_cmds *all_cmd, int count,
				char **ep, int *vars);
int			prepare_redir_append(t_list_cmds *full_cmd);
int			prepare_heredoc(t_list_cmds *full_cmd);
int			construct_cmd(t_list_cmds *full_cmd);
int			construct_cmd1(t_list_cmds *full_cmd);
void		prepare_redir(t_list_cmds *full_cmd);
void		prepare_inredir(t_list_cmds *full_cmd);
void		cleanup_alleof(t_list_cmds *full_cmd);
void		free_arg(char **arg);

// redir utils
void		update_infile(t_list_cmds *full_cmd, char *file_name, int count);
void		update_outfile(t_list_cmds *full_cmd, int count);
int			prep_exec_infile(t_list_cmds *cmd, int *pfd);
int			prep_exec_hdfile(t_list_cmds *cmd, int *pfd);
int			get_cmdlet_count(char **cmd_arr);
int			is_redir_char(char *arg);
int			is_append_char(char *arg);
int			is_inredirect_char(char *arg);
int			is_heredoc_char(char *arg);

//redir heredoc utils
int			is_valid_eof(char *str, char *limiter);
int			check_heredoc(char *str, char *eof, int *stdin_tmp, int *pipefd);
void		clean_sigint(int *stdin_tmp, int *pipefd, char *str);
void		dup2_close(int *stdin_tmp, int *pipefd);

// file
int			handle_file(t_list_cmds *cmd, int i);
int			check_file_inredir(char *file_name);

// exec
int			exec_cmds(t_list_cmds *cmds, char ***ep, int *c_ls,
				int (*func_ptr)(int*, int*, int*));
int			exec_and_get_status(t_list_cmds *cmds, int *c_ls,
				char ***ep, int *track_fds);
int			prepare_child_stdin(t_list_cmds *cmd, int *prev_read, int *pfd);
int			read_heredoc(t_list_cmds *cmd, char **ep, int *vars);
char		*parse_heredoc_delim(const char *s);
int			get_exitcode(char *cmd_name, int err_no);
void		cleanup_child(t_list_cmds *cmds, int *status,
				char ***ep, int *vals);

// built-in cmds
int			ft_echo(char **args);
int			ft_pwd(void);
int			ft_env(char **args, char **ep);
int			count_args(char **args);
int			ft_cd(char **args, char **ep);
int			parse_sign(const char *str, int *sign, int *valid);
int			ft_exit(t_list_cmds *cmd, char ***ep, int *vars, int track_fds);
int			ft_export(char **args, char ***ep, int *last_status);
int			ft_unset(char **args, char ***ep);
int			run_builtin(t_list_cmds *cmd, char ***ep,
				int last_status, int track_fds);
char		*get_env_var(char **env, const char *name);
void		set_env_var(char **env, const char *name, const char *value);
long		atol_valid(const char *str, int *valid);
void		exit_cleanup_vars(t_list_cmds *cmd, char ***ep, int track_fds);

// utils
char		**dup_env(char **ep);
char		*get_path_value(char **ep);
void		setup_signals(void);
void		heredoc_signal(void);
void		setup_child_signals(void);
void		setup_heredoc_signals(void);
int			ft_setenv(char ***ep, const char *name, const char *value);
void		update_shlvl(char ***envp);
//error
int			read_file_error(char *file);
int			redir_error(void);
int			err_pipe(char *line);

#endif
