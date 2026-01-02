/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 17:02:17 by ksan              #+#    #+#             */
/*   Updated: 2025/12/27 17:02:17 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rephrase_cmd(t_list_cmds *all_cmd, int count)
{
	int	i;
	(void)all_cmd;
	i = -1;
	while (++i < count)
	{
		prepare_redir_append(&all_cmd[i]);
		prepare_redir(&all_cmd[i]);
		prepare_inredir(&all_cmd[i]);
		prepare_heredoc(&all_cmd[i]);
		construct_cmd1(&all_cmd[i]);
		construct_cmd(&all_cmd[i]);
	}
}
