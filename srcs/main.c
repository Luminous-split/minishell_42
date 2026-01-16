/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:48:34 by soemin            #+#    #+#             */
/*   Updated: 2026/01/13 17:11:24 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

static void	eof_exit(int track_fds)
{
	if (track_fds == 1)
		close(0);
	else if (track_fds == 2)
		close(1);
	else if (track_fds == 3)
	{
		close(0);
		close(1);
	}
}

static void	parse_and_exec(char *line, char ***ep, int *vars)
{
	t_list_cmds	*cmds;

	cmds = NULL;
	if (prepare_cmds(&cmds, line, *ep, vars) == -1)
		vars[0] = 1;
	if (line != NULL)
		free(line);
	vars[0] = exec_and_get_status(cmds,
			(int []){vars[1], vars[0]},
			ep, &vars[2]);
}

static void	init_vars(int ac, char **av, int *ls_cc_fds)
{
	(void)ac;
	(void)av;
	ls_cc_fds[0] = 0;
	ls_cc_fds[1] = 0;
	ls_cc_fds[2] = 0;
	setup_signals();
}

static void	run_shell(char ***ep, int *ls_cc_fds)
{
	char	*line;

	while (1)
	{
		line = readline("⟢ minishellঌ♨️ ঌ 𖠣 ");
		if (!line)
		{
			eof_exit(ls_cc_fds[2]);
			break ;
		}
		if (g_signal == 1)
			ls_cc_fds[0] = 130;
		if (*line && is_invalid_line(line))
		{
			ls_cc_fds[0] = err_pipe(line);
			continue ;
		}
		else if (*line && check_pending(line))
			handle_pending_pipe(&line);
		if (line)
			add_history(line);
		if (line && line[0] != 0)
			parse_and_exec(line, ep, ls_cc_fds);
	}
}

int	main(int ac, char **av, char **envp)
{
	int		i;
	int		ls_cc_fds[3];
	char	**ep;

	i = -1;
	init_vars(ac, av, ls_cc_fds);
	ep = dup_env(envp);
	update_shlvl(&ep);
	run_shell(&ep, ls_cc_fds);
	while (ep[++i])
		free(ep[i]);
	free(ep);
	return (0);
}
