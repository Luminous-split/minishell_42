/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:34:46 by ksan              #+#    #+#             */
/*   Updated: 2025/10/02 13:18:51 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list_args	*cmd_parse(char *line, int *cmd_count)
{
	t_list_args	*cmds;
	t_list_args	cmd;
	int			next_size;

	cmds = NULL;
	cmd_str = ft_strtok(line, "|");
	while (cmd_str)
	{
		cmd.args = ft_split(argv[cmd_start], ' '); //split and unpack
		if (cmd.args[0] == NULL)
		{
			free(cmd.args);
			cmd.args = malloc(sizeof(char *) * 2);
			cmd.args[0] = ft_strdup(argv[cmd_start]);
			cmd.args[1] = NULL;
		}
		trim_cmdargs(cmd.args);
		next_size = ((*cmd_count) + 1) * sizeof(t_list_args);
		cmds = ft_realloc(cmds, (*cmd_count) * sizeof(t_list_args), next_size);
		cmds[(*cmd_count)++] = cmd;
		cmd_str = ft_strtok(NULL, "|");
	}
	return (cmds);
}
