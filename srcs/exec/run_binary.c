/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_binary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:18:02 by soemin            #+#    #+#             */
/*   Updated: 2025/09/29 18:18:23 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

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

static void	exec_in_path(const char *dir, char **args)
{
	char	full_path[PATH_MAX];

	join_path(full_path, dir, args[0]);
	execve(full_path, args, environ);
}

static	void	exec_binary(char **args)
{
	char	*path_env;
	char	*path_copy;
	char	*dir;

	path_env = getenv("PATH");
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
		exec_in_path(dir, args);
		dir = ft_strtok(NULL, ":");
	}
	free(path_copy);
	exit(EXIT_FAILURE);
}

static void	child_process(char **args)
{
	if (ft_strchr(args[0], '/'))
	{
		execve(args[0], args, environ);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	exec_binary(args);
}

int	run_binary(char **args)
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
		child_process(args);
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
