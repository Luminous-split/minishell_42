/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_prep_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 13:38:45 by ksan              #+#    #+#             */
/*   Updated: 2026/01/16 13:38:45 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prep_exec_infile(t_list_cmds *cmd, int *pfd)
{
	int	in_fd;

	in_fd = open(cmd->file_toread, O_RDONLY);
	if (in_fd == -1 || cmd->f_in == 1)
	{
		close(pfd[0]);
		close(pfd[1]);
		return (-1);
	}
	dup2(in_fd, 0);
	close(in_fd);
	return (0);
}

int	prep_exec_hdfile(t_list_cmds *cmd, int *pfd)
{
	if (*(cmd->hd_canceled) == 1)
	{
		close(pfd[0]);
		close(pfd[1]);
		return (1);
	}
	dup2(cmd->heredoc_fd, 0);
	close(cmd->heredoc_fd);
	cmd->heredoc_fd = -1;
	return (0);
}
