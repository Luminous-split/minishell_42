/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 20:29:19 by soemin            #+#    #+#             */
/*   Updated: 2025/10/02 18:54:39 by ksan             ###   ########.sg       */
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
	char	**cmds;
}	t_list_cmds;

// Global Variable for received signal

//FUNCTIONS

// parser
char	*ft_strtok(char *str, const char *delim);
void	expand_dollar(const char *line, char *tok, char **envp, int last_status);
char    *handle_single_quotes(const char *line, int start, char *tok);
char    *handle_double_quotes(const char *line, int start, char **envp, int last_status);

void		parse_path(t_list_cmds *cmds, char **envp, int count);
t_list_cmds     *cmd_parse(char *line);
void		*ft_realloc(void *ptr, size_t old_size, size_t new_size);
void            free_all(t_list_cmds *cmds, int count);
char		*next_pipe_token(char *str);

// exec
int	run_binary(char **args, char **envp);

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
int		ft_unset(char **args, char *var_nam);
int		run_builtin(char **args, char **envp, char *var_name, int last_status);
// utils
char	**dup_env(char **envp);
char	*get_path_value(char **envp);
int		ft_setenv(char ***envp, const char *name, const char *value);
void	setup_signals(void);
#endif
