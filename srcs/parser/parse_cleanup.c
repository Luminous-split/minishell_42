/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 15:07:05 by ksan              #+#    #+#             */
/*   Updated: 2026/01/01 15:07:05 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clean_vars(t_list_cmds *cmd)
{
	if (cmd->file_toappend)
		free(cmd->file_toappend);
	if (cmd->f_out)
		free(cmd->f_out);
	if (cmd->heredoc_fd != -1)
		close(cmd->heredoc_fd);
	if (cmd->file_toread)
	{
		free(cmd->file_toread);
		cmd->file_toread = NULL;
	}
	if (cmd->eof)
	{
		free(cmd->eof);
		cmd->eof = NULL;
	}
}

static void	clean_eof(t_list_cmds *cmd)
{
	int	i;

	i = -1;
	if (cmd->all_eof)
	{
		while (cmd->all_eof[++i])
			free(cmd->all_eof[i]);
		free(cmd->all_eof);
	}
}

static void	clean_args(t_list_cmds *cmd)
{
	int	i;

	i = -1;
	if (cmd->args)
	{
		while (cmd->args[++i])
			free(cmd->args[i]);
		free(cmd->args);
	}
}

void	cleanup_cmd(t_list_cmds *cmds, int cmd_count)
{
	int	i;

	if (!cmds)
		return ;
	i = -1;
	free(cmds->hd_canceled);
	cmds->hd_canceled = NULL;
	while (++i < cmd_count)
	{
		clean_vars(&cmds[i]);
		clean_eof(&cmds[i]);
		clean_args(&cmds[i]);
	}
	if (cmds)
		free(cmds);
	cmds = NULL;
}
