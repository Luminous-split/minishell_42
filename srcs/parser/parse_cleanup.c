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

static void	clean_eof(t_list_cmds cmd)
{
	int	i;

	i = -1;
	while (cmd.all_eof[++i])
		free(cmd.all_eof[i]);
	free(cmd.all_eof);
}

static void	clean_args(t_list_cmds cmd)
{
	int	i;

	i = -1;
	while (cmd.args[++i])
		free(cmd.args[i]);
	free(cmd.args);
}

void	parse_cleanup(t_list_cmds *cmds, int cmd_count)
{
	int	i;

	if (!cmds)
		return ;
	i = -1;
	while (++i < cmd_count)
	{
		if (cmds[i].file_toappend)
			free(cmds[i].file_toappend);
		if (cmds[i].file_toread)
			free(cmds[i].file_toread);
		if (cmds[i].eof)
			free(cmds[i].eof);
		if (cmds[i].all_eof)
			clean_eof(cmds[i]);
		clean_args(cmds[i]);
	}
	free(cmds);
	cmds = NULL;
}
