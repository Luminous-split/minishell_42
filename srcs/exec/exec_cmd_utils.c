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

static int	child_func(int *pipefd, int *idx, t_list_cmds *cmds)
{
	int	i;
	int	count;
	int	out_fd;

	i = idx[0];
	count = idx[1];
	close(pipefd[0]);
	if (cmds[i].file_toappend)
	{
		out_fd = open(cmds[i].file_toappend, O_WRONLY | O_APPEND);
		dup2(out_fd, 1);
		close(out_fd);
	}
	else if (i  < count - 1)
		dup2(pipefd[1], 1);
	close(pipefd[1]);

	if (!cmds[i].args[0])
		return (-1);
	if (execve(cmds[i].args[0], cmds[i].args, NULL) == -1)
	{
		perror(cmds[i].args[0]);
		return (get_exitcode(errno));
	}
	return (0);
}

static void	parent(int *pipefd, int *prev_read, int *util)
{
	close(pipefd[1]);
	if (*prev_read != -1)
		close(*prev_read);
	if (util[0] < util[1] - 1)
		*prev_read = pipefd[0];
	else
		close(pipefd[0]);
}

static void	cleanup_child(t_list_cmds *cmds, int *status, int *vals)
{
	if (*status == -1)
	{
		*status = 0;
		cleanup_cmd(cmds, vals[1]);
		close(0);
		close(1);
		exit(0);
	}
}

static void	prepare_child_stdin(t_list_cmds cmd, int *prev_read)
{
	int	in_fd;

	if (cmd.file_toread)
	{
		in_fd = open(cmd.file_toread, O_RDONLY);
		dup2(in_fd, 0);
		close(in_fd);
	}
	else if (cmd.heredoc_fd != -1)
	{
		dup2(cmd.heredoc_fd, 0);
		close(cmd.heredoc_fd);
	}
	else if (*prev_read != -1)
	{
		dup2(*prev_read, 0);
		close(*prev_read);
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
			prepare_child_stdin(cmds[i], &prev_read);
			status[1] = child_func(pipefd, (int []){i, count}, cmds);
			cleanup_child(cmds, &status[1], (int []){i, count});
		}
		else
			parent(pipefd, &prev_read, (int []){i, count});
	}
	while (waitpid(pid, &status[0], 0) > 0)
		continue ;
	return (WEXITSTATUS(status[0]));
}
