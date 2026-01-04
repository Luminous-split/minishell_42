/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 11:23:31 by ksan              #+#    #+#             */
/*   Updated: 2026/01/04 13:57:34 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_eof(char *str, char *limiter)
{
	char	*temp;

	temp = limiter;
	if (ft_strncmp(str, temp, ft_strlen(temp)) == 0
		&& ft_strlen(str) == ft_strlen(temp))
		return (1);
	return (0);
}

int	read_heredoc(char *eof, char **envp, int last_status)
{
	int	pipefd[2];
	char	*str;

	if (pipe(pipefd) < 0)
	{
		perror("pipe failed");
		exit(1);
	}
	while (1)
	{
		str = readline("> ");
//		unpack_token(str, envp, last_status);
		printf("Lstat: %d: TestEnvp: %s", last_status, envp[0]);
		if (is_valid_eof(str, eof) == 1 || str == NULL)
		{
			free(str);
			break ;
		}
		ft_putendl_fd(str, pipefd[1]);
		free(str);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}
