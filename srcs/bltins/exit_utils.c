/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:33:37 by soemin            #+#    #+#             */
/*   Updated: 2025/09/22 18:33:39 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_cleanup_arrs(t_list_cmds *cmd, char ***ep)
{
	int	i;

	i = -1;
	if (cmd->all_eof)
	{
		while (cmd->all_eof[++i])
			free(cmd->all_eof[i]);
		free(cmd->all_eof);
	}
	if (*ep != NULL)
	{
		while ((*ep)[++i])
			free((*ep)[i]);
		free(*ep);
		*ep = NULL;
	}
	i = -1;
	while (cmd->args[++i])
	{
		free(cmd->args[i]);
		cmd->args[i] = NULL;
	}
	free(cmd->args);
	cmd->args = NULL;
}

void	exit_cleanup_vars(t_list_cmds *cmd, char ***ep, int track_fds)
{
	int	i;

	i = -1;
	if (track_fds == 1)
		close(0);
	else if (track_fds == 2)
		close(1);
	else if (track_fds == 3)
	{
		close(0);
		close(1);
	}
	if (cmd->file_toappend)
		free(cmd->file_toappend);
	if (cmd->file_toread)
		free(cmd->file_toread);
	if (cmd->heredoc_fd != -1)
		close(cmd->heredoc_fd);
	if (cmd->eof)
		free(cmd->eof);
	exit_cleanup_arrs(cmd, ep);
	free(cmd);
}

int	parse_sign(const char *str, int *sign, int *valid)
{
	int	i;

	i = 0;
	*sign = 1;
	*valid = 1;
	if (!str)
	{
		*valid = 0;
		return (0);
	}
	if (str[0] == '+')
		i++;
	else if (str[0] == '-')
	{
		*sign = -1;
		i++;
	}
	return (i);
}

long	atol_valid(const char *str, int *valid)
{
	unsigned long	result;
	int				sign;
	int				i;

	result = 0;
	i = parse_sign(str, &sign, valid);
	if (!*valid)
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			*valid = 0;
			return (0);
		}
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
