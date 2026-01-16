/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_bltins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:48:28 by soemin            #+#    #+#             */
/*   Updated: 2026/01/16 12:15:43 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	check_validity(t_list_cmds *cmd)
{
	if (!(cmd->args) || !(cmd->args)[0])
		return (0);
	else if (*(cmd->hd_canceled) == 1)
		return (130);
	else
		return (1);
}

static int	run_pwd(char **args)
{
	if (!args[1])
		return (ft_pwd());
	else
		return (ft_putendl_fd("pwd: too many arguments", 2), 1);
}

int	run_builtin(t_list_cmds *cmd, char ***ep, int last_status, int track_fds)
{
	int		ret_val;
	char	**args;

	args = cmd->args;
	ret_val = 0;
	ret_val = check_validity(cmd);
	if (ret_val != 1)
		return (ret_val);
	if (ft_strncmp(args[0], "pwd", 3) == 0 && args[0][3] == '\0')
		return (run_pwd(args));
	if (ft_strncmp(args[0], "env", 3) == 0 && args[0][3] == '\0')
		return (ft_env(args, *ep));
	if (ft_strncmp(args[0], "echo", 4) == 0 && args[0][4] == '\0')
		return (ft_echo(args));
	if (ft_strncmp(args[0], "exit", 4) == 0 && args[0][4] == '\0')
		return (ft_exit(cmd, ep, (int []){last_status, 0}, track_fds));
	if (ft_strncmp(args[0], "cd", 2) == 0 && args[0][2] == '\0')
		return (ft_cd(args, *ep));
	if (ft_strncmp(args[0], "export", 6) == 0 && args[0][6] == '\0')
		return (ft_export(args, ep, &last_status));
	if (ft_strncmp(args[0], "unset", 5) == 0 && args[0][5] == '\0')
		return (ft_unset(args, ep));
	return (0);
}
