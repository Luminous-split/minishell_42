/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 13:08:54 by ksan              #+#    #+#             */
/*   Updated: 2026/01/09 11:53:11 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	prepare_child_stdin(t_list_cmds *cmd, int *prev_read, int *pfd)
{
	if (cmd->file_toread || (cmd->heredoc_fd != -1))
	{
		if (*prev_read != -1)
			close(*prev_read);
		*prev_read = -1;
	}
	if (cmd->file_toread)
	{
		if (prep_exec_infile(cmd, pfd) == -1)
			return (read_file_error(cmd->file_toread));
	}
	else if (cmd->heredoc_fd != -1)
	{
		if (prep_exec_hdfile(cmd, pfd) == -1)
			return (1);
	}
	else if (*prev_read != -1)
	{
		dup2(*prev_read, 0);
		close(*prev_read);
		*prev_read = -1;
	}
	return (0);
}

int	get_exitcode(char *cmd_name, int err_no)
{
	struct stat	st;

	ft_putstr_fd("minishell: '", 2);
	ft_putstr_fd(cmd_name, 2);
	ft_putstr_fd("' : ", 2);
	if (err_no == ENOENT)
		ft_putendl_fd("command not found", 2);
	else if (stat(cmd_name, &st) == 0 && S_ISDIR(st.st_mode))
		ft_putendl_fd("Is a directory", 2);
	else
		perror(NULL);
	if (err_no == ENOENT)
		return (127);
	else if (err_no == EACCES || err_no == EISDIR || err_no == ENOEXEC
		|| err_no == ETXTBSY || err_no == ELOOP || err_no == ENAMETOOLONG
		|| err_no == ENOTDIR)
		return (126);
	else
		return (1);
}

static void	free_line_envp(char ***ep)
{
	int	i;

	i = -1;
	if (*ep != NULL)
	{
		while ((*ep)[++i])
			free((*ep)[i]);
		free(*ep);
		*ep = NULL;
	}
}

void	cleanup_child(t_list_cmds *cmds, int *status, char ***ep, int *vals)
{
	free_line_envp(ep);
	if (*status == -1)
	{
		*status = 0;
		cleanup_cmd(cmds, vals[1]);
		close(0);
		close(1);
		exit(0);
	}
	else if (*status != 0)
	{
		cleanup_cmd(cmds, vals[1]);
		close(0);
		close(1);
		exit(*status);
	}
	else if (cmds[vals[0]].bltin == 1)
	{
		cleanup_cmd(cmds, vals[1]);
		close(0);
		close(1);
		exit(*status);
	}
}
