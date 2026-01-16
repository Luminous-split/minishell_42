/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 13:08:54 by ksan              #+#    #+#             */
/*   Updated: 2026/01/13 17:08:10 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	run(t_list_cmds cmd, char ***ep, int last_status)
{
	int	code;

	code = 0;
	if (strncmp(cmd.args[0], "exit", 4) == 0 && cmd.args[0][4] == '\0')
	{
		code = ft_exit(&cmd, ep, (int []){last_status, 1}, 0);
		return (code);
	}
	else if (cmd.bltin == 1)
		return (run_builtin(&cmd, ep, last_status, 0));
	else if (execve(cmd.args[0], cmd.args, *ep) == -1)
		return (get_exitcode(cmd.args[0], errno));
	else
		return (0);
}

static int	child_func(int *pipefd, char ***ep, int *i_c_ls, t_list_cmds *cmds)
{
	int	i;
	int	count;
	int	out_fd;

	i = i_c_ls[0];
	count = i_c_ls[1];
	close(pipefd[0]);
	if (cmds[i].file_toappend)
	{
		if (cmds[i].f_out != NULL)
		{
			close(pipefd[1]);
			return (read_file_error(cmds[i].f_out));
		}
		out_fd = open(cmds[i].file_toappend,
				O_WRONLY | O_APPEND | O_CREAT, 0644);
		dup2(out_fd, 1);
		close(out_fd);
	}
	else if (i < count - 1)
		dup2(pipefd[1], 1);
	close(pipefd[1]);
	if (!cmds[i].args[0])
		return (-1);
	return (run(cmds[i], ep, i_c_ls[2]));
}

static void	parent(int *pipefd, int *prev_read, int *util)
{
	if (pipefd[1] != -1)
	{
		close(pipefd[1]);
		pipefd[1] = -1;
	}
	if (*prev_read != -1)
		close(*prev_read);
	if (util[0] < util[1] - 1)
		*prev_read = pipefd[0];
	else
	{
		close(pipefd[0]);
		*prev_read = -1;
	}
}

static int	start_child(t_list_cmds *cmds, char ***ep, int *pipefd, int *vars[])
{
	int	status;
	int	i;
	int	*prev_read;

	status = 0;
	i = *(vars[1]);
	prev_read = vars[0];
	if (*(cmds->hd_canceled))
	{
		status = 130;
		close(pipefd[0]);
		close(pipefd[1]);
	}
	else
		status = prepare_child_stdin(&cmds[i], prev_read, pipefd);
	if (status != 1 && status != 130)
		status = child_func(pipefd, ep,
				(int []){i, vars[2][0], vars[2][1]}, cmds);
	cleanup_child(cmds, &status, ep, (int []){i, vars[2][0]});
	return (status);
}

int	exec_cmds(t_list_cmds *cmds, char ***ep, int *c_ls,
	int (*func_ptr)(int*, int*, int*))
{
	int	i;
	int	pipefd[2];
	int	status[2];
	int	pid;
	int	prev_read;

	func_ptr(status, &pid, &i);
	prev_read = -1;
	while (++i < c_ls[0])
	{
		pipe(pipefd);
		pid = fork();
		setup_child_signals();
		if (pid == 0)
			status[1] = start_child(cmds, ep, pipefd,
					(int *[]){&prev_read, &i, c_ls});
		else
			parent(pipefd, &prev_read, (int []){i, c_ls[0]});
		signal(SIGINT, SIG_IGN);
	}
	while (waitpid(pid, &status[0], 0) > 0)
		continue ;
	setup_signals();
	return (WEXITSTATUS(status[0]));
}
