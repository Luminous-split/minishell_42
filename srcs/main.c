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

int	main(int ac, char **av, char **envp)
{
	char	*line;
	char	**args;
	int		last_status;
	char	**my_env;
	t_list_args	*cmds;
	int	cmd_count;

	(void)ac;
	(void)av;
	(void)envp;

	cmds = NULL;
	cmd_count = 0;
	last_status = 0;
	*my_env = dup_env(envp);
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
		if (is_builtin(args))
			run_builtin(args, &envp, last_status);
		else if (strchr(args, '|'))
			cmds = cmd_parse(line, 0);
		else
			run_binary(args, my_env);
		free(args);
		free(line);
	}
	return (0);
}
