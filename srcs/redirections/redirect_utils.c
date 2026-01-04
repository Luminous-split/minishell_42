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

static void	cleanup_alleof(t_list_cmds *full_cmd)
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

void	handle_one_heredoc(t_list_cmds *full_cmd, int count)
{
	int	i;

	i = -1;
	while (++i < count)
	{
		if (is_heredoc_char(full_cmd->args[i]))
			full_cmd->eof = ft_strdup(full_cmd->args[i + 1]);
	}
	cleanup_alleof(full_cmd);
}

void	update_chosen_heredoc(t_list_cmds *full_cmd)
{
	int		index;
	char	*line;
	char	*temp_ptr;

	line = readline("> ");
	index = 0;
	while (line)
	{
		temp_ptr = full_cmd->all_eof[index];
		if (ft_strncmp(line, temp_ptr, ft_strlen(temp_ptr)) == 0
			&& ft_strlen(temp_ptr) == ft_strlen(line))
		{
			if (full_cmd->all_eof[index + 2] == NULL)
			{
				full_cmd->eof = ft_strdup(full_cmd->all_eof[index + 1]);
				cleanup_alleof(full_cmd);
				free(line);
				break ;
			}
			index++;
		}
		free(line);
		line = readline("> ");
	}
}

void	update_infile(t_list_cmds *full_cmd, char *temp_name, int count)
{
	while (--count)
	{
		if (is_heredoc_char(full_cmd->args[count - 1]))
			break ;
		else if (is_inredirect_char(full_cmd->args[count - 1]))
		{
			free(full_cmd->eof);
			full_cmd->eof = NULL;
			full_cmd->file_toread = ft_strdup(temp_name);
			break ;
		}
	}
}
