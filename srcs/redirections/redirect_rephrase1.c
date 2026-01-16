/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_rephrase1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 17:18:53 by ksan              #+#    #+#             */
/*   Updated: 2025/12/28 14:14:12 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_count_inredir(t_list_cmds *full_cmd, int count)
{
	int		to_reduce;
	int		i;
	char	*temp_name;

	i = -1;
	temp_name = NULL;
	to_reduce = 0;
	while (++i < count)
	{
		if (is_heredoc_char(full_cmd->args[i]))
			i++;
		else if (is_inredirect_char(full_cmd->args[i]))
		{
			if (!full_cmd->f_in)
				temp_name = full_cmd->args[++i];
			if (!check_file_inredir(full_cmd->args[i]))
				full_cmd->f_in = 1;
			to_reduce++;
		}
	}
	update_infile(full_cmd, temp_name, count);
	return (to_reduce * 2);
}

static int	get_count_heredoc(t_list_cmds *full_cmd, int count)
{
	int		new_count;
	int		i;
	int		size;
	size_t	new_size;

	size = 0;
	new_size = 0;
	i = -1;
	new_count = 0;
	while (++i < count)
	{
		if (is_heredoc_char(full_cmd->args[i]))
		{
			new_size = sizeof(char *) * (size + 2);
			full_cmd->all_eof = ft_realloc(full_cmd->all_eof,
					sizeof(char *) * (size++), new_size);
			full_cmd->all_eof[size - 1] = ft_strdup(full_cmd->args[++i]);
		}
		else
			new_count++;
	}
	if (size > 0)
		full_cmd->all_eof[size] = NULL;
	return (new_count);
}

static int	check_validity(t_list_cmds *full_cmd)
{
	int	count;
	int	i;

	i = -1;
	count = get_cmdlet_count(full_cmd->args);
	while (++i < count)
	{
		if (is_heredoc_char(full_cmd->args[i])
			&& (full_cmd->args[i + 1] == NULL
				|| is_heredoc_char(full_cmd->args[i + 1])))
			return (redir_error());
		else if (is_inredirect_char(full_cmd->args[i])
			&& (full_cmd->args[i + 1] == NULL
				|| is_inredirect_char(full_cmd->args[i + 1])))
			return (redir_error());
	}
	return (count);
}

static void	final_cmd(t_list_cmds *full_cmd, int old_count, int new_count)
{
	int		i;
	int		new_i;
	char	**new_cmd;

	i = -1;
	new_i = 0;
	new_cmd = malloc(sizeof(char *) * (new_count + 1));
	while (++i < old_count)
	{
		if (is_heredoc_char(full_cmd->args[i])
			|| is_inredirect_char(full_cmd->args[i]))
			i++;
		else
			new_cmd[new_i++] = ft_strdup(full_cmd->args[i]);
	}
	new_cmd[new_count] = NULL;
	free_arg(full_cmd->args);
	full_cmd->args = new_cmd;
}

int	construct_cmd1(t_list_cmds *full_cmd)
{
	int	i;
	int	count;
	int	new_count;

	i = -1;
	count = check_validity(full_cmd);
	if (count == -1)
		return (-1);
	new_count = get_count_heredoc(full_cmd, count);
	new_count = new_count - get_count_inredir(full_cmd, count);
	final_cmd(full_cmd, count, new_count);
	return (1);
}
