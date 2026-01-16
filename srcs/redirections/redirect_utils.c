/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 15:33:50 by ksan              #+#    #+#             */
/*   Updated: 2026/01/04 16:26:30 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_alleof(t_list_cmds *full_cmd)
{
	int	i;

	i = -1;
	if (!full_cmd)
		return ;
	while (full_cmd->all_eof[++i])
		free(full_cmd->all_eof[i]);
	free(full_cmd->all_eof);
	full_cmd->all_eof = NULL;
}

void	update_infile(t_list_cmds *full_cmd, char *temp_name, int count)
{
	if (count <= 0)
		return ;
	while (--count)
	{
		if (is_heredoc_char(full_cmd->args[count - 1]))
			break ;
		else if (is_inredirect_char(full_cmd->args[count - 1]))
		{
			free(full_cmd->eof);
			full_cmd->eof = NULL;
			if (full_cmd->file_toread == NULL)
				full_cmd->file_toread = ft_strdup(temp_name);
			break ;
		}
	}
}

void	update_outfile(t_list_cmds *full_cmd, int count)
{
	if (count <= 0)
		return ;
	while (--count)
	{
		if (is_redir_char(full_cmd->args[count - 1]))
		{
			if (full_cmd->file_toappend == NULL)
				full_cmd->file_toappend = ft_strdup(full_cmd->args[count]);
			break ;
		}
		else if (is_append_char(full_cmd->args[count - 1]))
		{
			if (full_cmd->file_toappend == NULL)
				full_cmd->file_toappend = ft_strdup(full_cmd->args[count]);
			break ;
		}
	}
}
