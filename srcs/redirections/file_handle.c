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
	if (open(file_name, O_RDONLY) < 0)
	{
		perror(file_name);
		return (0);
	}
	else
		return (1);
}

int	handle_file(char *file_name, int is_append)
{
	int	check_fd;
	int	fd;

	check_fd = open(file_name, O_WRONLY);
	if (check_fd < 0)
	{
		if (errno == ENOENT)
		{
			fd = open(file_name, O_WRONLY | O_CREAT, 0644);
			close(fd);
			return (1);
		}
		else
		{
			perror(file_name);
			return (-1);
		}
	}
	else if (is_append)
		fd = open(file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		fd = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd >= 0)
		close(fd);
	if (check_fd >= 0)
		close(check_fd);
	return (1);
}
