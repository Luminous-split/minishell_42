/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 10:58:24 by ksan              #+#    #+#             */
/*   Updated: 2025/06/25 18:14:00 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_values(int *status, int *pid, int *i)
{
	*i = -1;
	*pid = 0;
	status[0] = 0;
	status[1] = 0;
}

/*
static int	prepare_files(int *inp_fd, int *out_fd)
{
	*inp_fd = open(argv[1], O_RDONLY);
	if (*inp_fd < 0)
	{
		perror(argv[1]);
		*out_fd = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (*out_fd < 0)
			perror(argv[argc - 1]);
		close(*out_fd);
		return (1);
	}
	*out_fd = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (*out_fd < 0)
	{
		close(*inp_fd);
		perror(argv[argc - 1]);
		return (1);
	}
	return (0);
}
*/
int	exec_and_get_status(t_list_cmds *cmds, int cmd_count)
{
	int			exit_status;

	exit_status = 0;
	if (exit_status)
		return (1);
	exit_status = exec_cmds(cmds, cmd_count, (int (*)(int*, int*, int*))init_values);
	return (exit_status);
}
