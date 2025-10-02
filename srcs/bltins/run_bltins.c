/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_bltins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:48:28 by soemin            #+#    #+#             */
/*   Updated: 2025/10/02 13:32:00 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	is_builtin(char **av)
{
	if (!av ||!av[0])
		return (0);
	if (ft_strncmp(av[0], "pwd", 3) == 0 && av[0][3] == '\0')
		return (1);
	if (ft_strncmp(av[0], "env", 3) == 0 && av[0][3] == '\0')
		return (1);
	if (ft_strncmp(av[0], "echo", 4) == 0 && av[0][4] == '\0')
		return (1);
	if (ft_strncmp(av[0], "exit", 4) == 0 && av[0][4] == '\0')
		return (1);
	if (ft_strncmp(av[0], "cd", 2) == 0 && av[0][2] == '\0')
		return (1);
	if (ft_strncmp(av[0], "export", 6) == 0 && av[0][6] == '\0')
		return (1);
	if (ft_strncmp(av[0], "unset", 5) == 0 && av[0][5] == '\0')
		return (1);
	return (0);
}

int	run_builtin(char **args, char ***envp, int last_status)
{
	if (!args || !args[0])
		return (0);
	if (ft_strncmp(args[0], "pwd", 3) == 0 && args[0][3] == '\0')
		return (ft_pwd());
	if (ft_strncmp(args[0], "env", 3) == 0 && args[0][3] == '\0')
		return (ft_env(args, *envp));
	if (ft_strncmp(args[0], "echo", 4) == 0 && args[0][4] == '\0')
		return (ft_echo(args));
	if (ft_strncmp(args[0], "exit", 4) == 0 && args[0][4] == '\0')
		return (ft_exit(args, last_status));
	if (ft_strncmp(args[0], "cd", 2) == 0 && args[0][2] == '\0')
		return (ft_cd(args, *envp));
	if (ft_strncmp(args[0], "export", 6) == 0 && args[0][6] == '\0')
		return (ft_export(args, envp, &last_status));
	if (ft_strncmp(args[0], "unset", 5) == 0 && args[0][5] == '\0')
		return (ft_unset(args, envp));
	return (0);
}
