/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:48:34 by soemin            #+#    #+#             */
/*   Updated: 2025/10/02 18:36:34 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
static void	info_printpipetokens(t_list_cmds *cmds, int cmd_count)
{
	int i = -1;
	while (++i < cmd_count)
	{
		printf("----------------------\n");
		printf(" Is>>?: %d; Is>?: %d. Arg %d: token: [", cmds[i].is_redir_gtgt, cmds[i].is_redir_gt, i);
		while (*(cmds[i].args))
		{
			printf("[%s]", *(cmds[i].args));
			(cmds[i].args)++;
		}
		printf("]\n");
		printf("----------------------\n");
	}
}
*/
int	main(int ac, char **av, char **envp)
{
	char	*line;
	int		last_status;
//	char	**my_env;
	t_list_cmds	*cmds;
	int	cmd_count;

	(void)ac;
	(void)av;
	(void)envp;

	cmds = NULL;
	cmd_count = 0;
	last_status = 0;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line)
			add_history(line);
		cmd_count = prepare_cmds(cmds, line, envp);
		last_status = exec_and_get_status(cmds, cmd_count);
		parse_cleanup(cmds, cmd_count);
		free(line);
	}
	return (0);
}
