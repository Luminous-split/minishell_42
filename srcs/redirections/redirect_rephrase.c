/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_rephrase.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 17:18:53 by ksan              #+#    #+#             */
/*   Updated: 2025/12/27 17:18:53 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_count(t_list_cmds *cmd, int count)
{
	int	new_count;
	int	succeed;
	int	i;

	i = -1;
	succeed = 0;
	new_count = 0;
	while (++i < count)
	{
		if (is_append_char(cmd->args[i]) || is_redir_char(cmd->args[i]))
		{
			i++;
			if (succeed == 0)
			{
				succeed = handle_file(cmd, i);
				if (succeed == -1)
					cmd->f_out = ft_strdup(cmd->args[i]);
			}
		}
		else
			new_count++;
	}
	update_outfile(cmd, count);
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
		if (is_append_char(full_cmd->args[i])
			&& (full_cmd->args[i + 1] == NULL
				|| is_append_char(full_cmd->args[i + 1])))
			return (redir_error());
		else if (is_redir_char(full_cmd->args[i])
			&& (full_cmd->args[i + 1] == NULL
				|| is_redir_char(full_cmd->args[i + 1])))
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
		if (is_append_char(full_cmd->args[i])
			|| is_redir_char(full_cmd->args[i]))
			i++;
		else
			new_cmd[new_i++] = ft_strdup(full_cmd->args[i]);
	}
	new_cmd[new_count] = NULL;
	free_arg(full_cmd->args);
	full_cmd->args = new_cmd;
}

int	construct_cmd(t_list_cmds *full_cmd)
{
	int	i;
	int	count;
	int	new_count;

	i = -1;
	count = check_validity(full_cmd);
	if (count == -1)
		return (-1);
	new_count = get_count(full_cmd, count);
	final_cmd(full_cmd, count, new_count);
	return (1);
}
