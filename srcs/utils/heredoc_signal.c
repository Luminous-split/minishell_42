/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 11:57:18 by ksan              #+#    #+#             */
/*   Updated: 2026/01/15 11:57:18 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_readline(void)
{
	return (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO));
}

static void	heredoc_sigint(int sig)
{
	(void)sig;
	g_signal = 130;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

void	heredoc_signal(void)
{
	struct sigaction	sa;

	signal(SIGQUIT, SIG_IGN);
	if (!is_readline())
		signal(SIGINT, SIG_DFL);
	else
	{
		sigemptyset(&sa.sa_mask);
		sa.sa_handler = heredoc_sigint;
		sa.sa_flags = 0;
		sigaction(SIGINT, &sa, NULL);
	}
}
