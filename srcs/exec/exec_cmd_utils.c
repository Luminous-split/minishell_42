/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 13:08:54 by ksan              #+#    #+#             */
/*   Updated: 2026/01/01 17:32:36 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_exitcode(int err_no)
{
	if (err_no == ENOENT)
		return (127);
	else if (err_no == EACCES || err_no == EISDIR || err_no == ENOEXEC
		|| err_no == ETXTBSY || err_no == ELOOP || err_no == ENAMETOOLONG
		|| err_no == ENOTDIR)
		return (126);
	else
		return (1);
}

static int	child_func(int *pipefd, int *prev_read, int *idx, t_list_cmds *cmds)
{
	int	i;
	int	count;

	i = idx[0];
	count = idx[1];
	if (*prev_read != -1)
	{
		dup2(*prev_read, 0);
		close(*prev_read);
	}
	close(pipefd[0]);
	if (cmds[i].file_toappend)
		dup2(pipefd[1], open(cmds[i].file_toappend, O_WRONLY));
	else if (i  < count - 1)
		dup2(pipefd[1], 1);
	close(pipefd[1]);
	if (execve(cmds[i].args[0], cmds[i].args, NULL) == -1)
	{
		perror(cmds[i].args[0]);
		return (get_exitcode(errno));
	}
	return (0);
}

static void	parent(int *pipefd, int *prev_read, int *util, t_list_cmds *cmds)
{
	close(pipefd[1]);
	if (cmds[util[0]].file_toread)
		pipefd[0] = open(cmds[util[0]].file_toread, O_RDONLY);
	else if (*prev_read != -1)
		*prev_read = pipefd[0];
	else
		close(pipefd[0]);
}

static void	cleanup_child(t_list_cmds *cmds, int status, int *vals)
{
	if (status != 0)
	{
		free_all(cmds, vals[1]);
		close(0);
		close(1);
		exit(status);
	}
}

int	exec_cmds(t_list_cmds *cmds, int count, int (*func_ptr)(int*, int*, int*))
{
	int	i;
	int	pipefd[2];
	int	status[2];
	int	pid;
	int	prev_read;

	func_ptr(status, &pid, &i);
	prev_read = -1;
	while (++i < count)
	{
		pipe(pipefd);
		pid = fork();
		if (pid == 0)
		{
			status[1] = child_func(pipefd, &prev_read, (int []){i, count}, cmds);
			cleanup_child(cmds, status[1], (int []){i, count});
		}
		else
			parent(pipefd, &prev_read, (int []){i, count}, cmds);
	}
	while (waitpid(pid, &status[0], 0) > 0)
		continue ;
	return (WEXITSTATUS(status[0]));
}
