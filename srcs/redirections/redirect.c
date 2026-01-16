/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 17:02:17 by ksan              #+#    #+#             */
/*   Updated: 2026/01/12 13:36:57 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	pre_read_heredoc(t_list_cmds *cmd, char **ep, int *vars)
{
	if (cmd->eof == NULL && cmd->all_eof == NULL)
		return ;
	else if (*(cmd->hd_canceled) != 1)
	{
		heredoc_signal();
		cmd->heredoc_fd = read_heredoc(cmd, ep, vars);
		setup_signals();
	}
}

static void	unpack_all(t_list_cmds *cmd, char **ep, int last_status)
{
	int		i;
	char	*temp_ptr;

	i = -1;
	while (cmd->args[++i])
	{
		temp_ptr = cmd->args[i];
		if (i >= 1 && is_heredoc_char(cmd->args[i - 1]))
			cmd->args[i] = strdup(cmd->args[i]);
		else
			cmd->args[i] = unpack_token(cmd->args[i], ep, last_status);
		free(temp_ptr);
	}
}

int	rephrase_cmd(t_list_cmds *all_cmd, int count, char **ep, int *vars)
{
	int	i;

	i = -1;
	while (++i < count)
	{
		prepare_inredir(&all_cmd[i]);
		prepare_heredoc(&all_cmd[i]);
		prepare_redir_append(&all_cmd[i]);
		prepare_redir(&all_cmd[i]);
		unpack_all(&all_cmd[i], ep, vars[0]);
		if (construct_cmd1(&all_cmd[i]) == -1)
		{
			cleanup_cmd(all_cmd, count);
			return (2);
		}
		if (construct_cmd(&all_cmd[i]) == -1)
		{
			cleanup_cmd(all_cmd, count);
			return (2);
		}
		pre_read_heredoc(&all_cmd[i], ep, vars);
	}
	return (0);
}
