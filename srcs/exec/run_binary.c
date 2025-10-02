/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_binary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:18:02 by soemin            #+#    #+#             */
/*   Updated: 2025/10/02 13:36:26 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	join_path(char *dst, const char *dir, const char *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dir[i])
	{
		dst[i] = dir[i];
		i++;
	}
	dst[i] = '/';
	i++;
	while (cmd[j])
	{
		dst[i] = cmd[j];
		j++;
		i++;
	}
	dst[i] = '\0';
}

static void	exec_in_path(const char *dir, char **args, char **envp)
{
	char	full_path[PATH_MAX];

	join_path(full_path, dir, args[0]);
	execve(full_path, args, envp);
}

static	void	exec_binary(char **args)
{
	char	*path_env;
	char	*path_copy;
	char	*dir;

	path_env = get_path_value(envp);
	if (!path_env)
	{
		printf("minishell: PATH not set\n");
		exit(EXIT_FAILURE);
	}
	path_copy = ft_strdup(path_env);
	if (!path_copy)
	{
		perror("strdup");
		exit(EXIT_FAILURE);
	}
	dir = ft_strtok(path_copy, ":");
	while (dir)
	{
		exec_in_path(dir, argsi, envp);
		dir = ft_strtok(NULL, ":");
	}
	free(path_copy);
	exit(EXIT_FAILURE);
}

static void	child_process(char **args, char **envp)
{
	if (ft_strchr(args[0], '/'))
	{
		execve(args[0], args, envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	exec_binary(args);
}

int	run_binary(char **args, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
		child_process(args, envp);
	else
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid");
			return (1);
		}
	}
	return (0);
}
