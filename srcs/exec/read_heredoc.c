/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 11:23:31 by ksan              #+#    #+#             */
/*   Updated: 2026/01/16 13:11:45 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_line_fd(t_list_cmds *cmd, char **ep,
	char *str, int *ls_idx_we)
{
	int	index;
	int	fd_we;
	int	last_status;

	last_status = ls_idx_we[0];
	index = ls_idx_we[1];
	fd_we = ls_idx_we[2];
	if (cmd->all_eof[index + 1] == NULL && !(cmd->file_toread))
	{
		str = unpack_token(str, ep, last_status);
		ft_putendl_fd(str, fd_we);
	}
}

static void	rhd_helper(t_list_cmds *cmd, int *ret_val, int *index)
{
	if (*ret_val == 1)
	{
		*(cmd->hd_canceled) = 1;
		return ;
	}
	else if (*ret_val == 2)
	{
		if (cmd->all_eof[*(index) + 1] == NULL)
			*ret_val = 3;
		else
			(*index)++;
		return ;
	}
}

static void	init_vars(int *ret_val, int *idx)
{
	g_signal = 0;
	*ret_val = 0;
	*idx = 0;
}

int	read_heredoc(t_list_cmds *cmd, char **ep, int *vars)
{
	int		pipefd[2];
	char	*str;
	int		stdin_tmp;
	int		idx;
	int		ret_val;

	pipe(pipefd);
	init_vars(&ret_val, &idx);
	stdin_tmp = dup(STDIN_FILENO);
	vars[2] = 1;
	while (1)
	{
		str = readline("> ");
		ret_val = check_heredoc(str, cmd->all_eof[idx], &stdin_tmp, pipefd);
		rhd_helper(cmd, &ret_val, &idx);
		if (ret_val == 1 || ret_val == 3)
			break ;
		else if (ret_val == 2)
			continue ;
		else if (ret_val == 0)
			write_line_fd(cmd, ep, str, (int []){vars[0], idx, pipefd[1]});
		free(str);
	}
	dup2_close(&stdin_tmp, pipefd);
	return (pipefd[0]);
}
