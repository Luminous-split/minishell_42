/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 11:53:51 by ksan              #+#    #+#             */
/*   Updated: 2026/01/04 11:53:51 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtin(char *cmd)
{
	size_t	len;

	len = ft_strlen(cmd);
	if (!strncmp(cmd, "echo", len) && len == ft_strlen("echo"))
		return (1);
	else if (!strncmp(cmd, "cd", len) && len == ft_strlen("cd"))
		return (1);
	else if (!strncmp(cmd, "pwd", len) && len == ft_strlen("pwd"))
		return (1);
	else if (!strncmp(cmd, "export", len) && len == ft_strlen("export"))
		return (1);
	else if (!strncmp(cmd, "unset", len) && len == ft_strlen("unset"))
		return (1);
	else if (!strncmp(cmd, "env", len) && len == ft_strlen("env"))
		return (1);
	else if (!strncmp(cmd, "exit", len) && len == ft_strlen("exit"))
		return (1);
	else
		return (0);
}

void	check_builtin(t_list_cmds *cmd, int cmd_count)
{
	int	i;
	char	*temp_ptr;

	i = -1;
	temp_ptr = NULL;
	while (++i < cmd_count)
	{
		temp_ptr = cmd[i].args[0];
		if (is_builtin(temp_ptr))
			cmd[i].bltin = 1;
	}
}
