/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 10:58:24 by ksan              #+#    #+#             */
/*   Updated: 2026/01/11 15:50:23 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_values(int *status, int *pid, int *i)
{
	*i = -1;
	*pid = 0;
	status[0] = 0;
	status[1] = 0;
}

static int	setup_file(t_list_cmds *cmd)
{
	int	tofd;

	if (cmd->file_toappend)
	{
		if (cmd->f_out != NULL)
			return (read_file_error(cmd->f_out));
		tofd = open(cmd->file_toappend, O_WRONLY | O_APPEND | O_CREAT, 0644);
		dup2(tofd, 1);
		close(tofd);
	}
	return (0);
}

static int	prepare_fds(t_list_cmds *cmd, int *stdin_bk, int *stdout_bk)
{
	int	temp_infd;

	if (ft_strncmp(cmd->args[0], "exit", 4) == 0
		&& cmd->args[0][4] == '\0')
		return (0);
	if (cmd->file_toread || cmd->heredoc_fd != -1)
		*stdin_bk = dup(STDIN_FILENO);
	if (cmd->file_toappend)
		*stdout_bk = dup(STDOUT_FILENO);
	if (cmd->file_toread)
	{
		temp_infd = open(cmd->file_toread, O_RDONLY);
		if (temp_infd == -1)
			return (read_file_error(cmd->file_toread));
		dup2(temp_infd, 0);
		close(temp_infd);
	}
	else if (cmd->heredoc_fd != -1 && *(cmd->hd_canceled) != 1)
	{
		dup2(cmd->heredoc_fd, 0);
		close(cmd->heredoc_fd);
		cmd->heredoc_fd = -1;
	}
	return (setup_file(cmd));
}

static void	restore_fds(int *stdin_bk, int *stdout_bk, int *track_fds)
{
	if (*stdin_bk >= 0)
	{
		dup2(*stdin_bk, STDIN_FILENO);
		close(*stdin_bk);
		*stdin_bk = -2;
	}
	if (*stdout_bk >= 0)
	{
		dup2(*stdout_bk, STDOUT_FILENO);
		close(*stdout_bk);
		*stdout_bk = -2;
	}
	if (*stdin_bk == -2)
		*track_fds = 1;
	if (*stdout_bk == -2)
		*track_fds = 2;
	if (*stdin_bk == -2 && *stdout_bk == -2)
		*track_fds = 3;
}

int	exec_and_get_status(t_list_cmds *cmds, int *c_ls,
		char ***ep, int *track_fds)
{
	int	exit_status;
	int	stdin_bk;
	int	stdout_bk;
	int	failed;

	failed = 0;
	exit_status = 0;
	stdin_bk = -1;
	stdout_bk = -1;
	if (c_ls[0] == 1 && cmds[0].bltin == 1)
	{
		failed = prepare_fds(&cmds[0], &stdin_bk, &stdout_bk);
		if (failed == 0)
			exit_status = run_builtin(&cmds[0], ep, c_ls[1], *track_fds);
		else
			exit_status = failed;
		restore_fds(&stdin_bk, &stdout_bk, track_fds);
	}
	else
		exit_status = exec_cmds(cmds, ep, (int []){c_ls[0], c_ls[1]},
				(int (*)(int*, int*, int*))init_values);
	cleanup_cmd(cmds, c_ls[0]);
	return (exit_status);
}
