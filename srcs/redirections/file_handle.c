/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 16:49:46 by ksan              #+#    #+#             */
/*   Updated: 2025/12/27 16:54:12 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_file_inredir(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

static void	fd_cleanup(int *fd, int *check_fd)
{
	if (*fd >= 0)
		close(*fd);
	if (*check_fd >= 0)
		close(*check_fd);
}

int	handle_file(t_list_cmds *cmd, int i)
{
	int		check_fd;
	int		fd;
	char	*file_name;

	file_name = cmd->args[i];
	if (ft_strlen(file_name) == 0)
		return (-1);
	check_fd = open(file_name, O_WRONLY);
	if (check_fd < 0)
	{
		if (errno == ENOENT && !(cmd->f_in))
		{
			fd = open(file_name, O_WRONLY | O_CREAT, 0644);
			close(fd);
			return (0);
		}
		else
			return (-1);
	}
	else if (is_append_char(cmd->args[i - 1]))
		fd = open(file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		fd = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	fd_cleanup(&fd, &check_fd);
	return (0);
}
