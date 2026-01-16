/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 18:32:58 by ksan              #+#    #+#             */
/*   Updated: 2025/10/02 18:55:00 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**extract_path(char **envp)
{
	char	**path;

	while (*envp)
	{
		if (!ft_strncmp(*envp, "PATH=", 5))
		{
			path = ft_split(*envp + 5, ':');
			return (path);
		}
		envp++;
	}
	return (NULL);
}

static char	*prefix(char *cmd, const char *prefix_dir)
{
	char	*out;
	size_t	prefix_len;
	size_t	cmd_len;

	prefix_len = ft_strlen(prefix_dir);
	cmd_len = ft_strlen(cmd);
	out = malloc(sizeof(char) * (prefix_len + cmd_len + 2));
	if (!out)
		return (NULL);
	ft_memcpy(out, prefix_dir, prefix_len);
	out[prefix_len] = '/';
	ft_memcpy(out + prefix_len + 1, cmd, cmd_len);
	out[prefix_len + cmd_len + 1] = '\0';
	return (out);
}

static int	valid(t_list_cmds *cmd, int i)
{
	if (ft_strlen(cmd[i].args[0])
		&& !(ft_strchr(cmd[i].args[0], '/'))
		&& cmd[i].bltin == -1)
		return (1);
	return (0);
}

static void	append_path(t_list_cmds *cmds, char **path, int count)
{
	int		i;
	int		j;
	char	*full_path;

	i = -1;
	while (++i < count)
	{
		j = -1;
		while (path[++j] && valid(cmds, i))
		{
			full_path = prefix(cmds[i].args[0], path[j]);
			if (access(full_path, X_OK) < 0)
			{
				free(full_path);
				continue ;
			}
			else
			{
				free(cmds[i].args[0]);
				cmds[i].args[0] = full_path;
				break ;
			}
		}
	}
}

void	parse_path(t_list_cmds *cmds, char **envp, int count)
{
	int		i;
	char	**path;

	path = extract_path(envp);
	check_builtin(cmds, count);
	if (!path)
		return ;
	append_path(cmds, path, count);
	i = -1;
	while (path[++i])
	{
		free(path[i]);
	}
	free(path);
}
