/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 17:02:17 by ksan              #+#    #+#             */
/*   Updated: 2025/12/27 17:02:17 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	pre_read_heredoc(t_list_cmds *cmd)
{
	if (cmd->eof == NULL)
		return ;
	if (cmd->file_toread)
		return ;
	else if (cmd->eof)
		cmd->heredoc_fd = read_heredoc(cmd->eof);
}

int	rephrase_cmd(t_list_cmds *all_cmd, int count)
{
	int	i;
	(void)all_cmd;
	i = -1;
	while (++i < count)
	{
		prepare_redir_append(&all_cmd[i]);
		prepare_redir(&all_cmd[i]);
		prepare_inredir(&all_cmd[i]);
		prepare_heredoc(&all_cmd[i]);

		if (construct_cmd1(&all_cmd[i]) == -1)
			return (2);
		if (construct_cmd(&all_cmd[i]) == -1)
			return (2);
		pre_read_heredoc(&all_cmd[i]);
	}
	return (0);
}
