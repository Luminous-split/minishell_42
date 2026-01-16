/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredoc_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:31:07 by ksan              #+#    #+#             */
/*   Updated: 2026/01/16 13:15:57 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_heredoc_delim(const char *s)
{
	int		i;
	int		j;
	char	q;
	char	*res;

	i = 0;
	j = 0;
	q = 0;
	res = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!res)
		return (NULL);
	while (s[i])
	{
		if ((s[i] == '\'' || s[i] == '"') && q == 0)
			q = s[i];
		else if (s[i] == q)
			q = 0;
		else
			res[j++] = s[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}

int	is_valid_eof(char *str, char *limiter)
{
	char	*temp;

	if (!str)
		return (0);
	if (!(*str))
		return (0);
	temp = parse_heredoc_delim(limiter);
	if (ft_strncmp(str, temp, ft_strlen(temp)) == 0
		&& ft_strlen(str) == ft_strlen(temp))
	{
		free(temp);
		return (1);
	}
	free(temp);
	return (0);
}

void	dup2_close(int *stdin_tmp, int *pipefd)
{
	if (*stdin_tmp != -1)
	{
		dup2(*stdin_tmp, STDIN_FILENO);
		close(*stdin_tmp);
		*stdin_tmp = -1;
	}
	if (pipefd[1] != -1)
	{
		close(pipefd[1]);
		pipefd[1] = -1;
	}
}

void	clean_sigint(int *stdin_tmp, int *pipefd, char *str)
{
	dup2(*stdin_tmp, STDIN_FILENO);
	close(*stdin_tmp);
	*stdin_tmp = -1;
	if (pipefd[1] != -1)
	{
		close(pipefd[1]);
		pipefd[1] = -1;
	}
	free(str);
}

int	check_heredoc(char *str, char *eof, int *stdin_tmp, int *pipefd)
{
	if (!str)
	{
		if (g_signal == 130)
		{
			clean_sigint(stdin_tmp, pipefd, str);
			return (1);
		}
		return (2);
	}
	if (is_valid_eof(str, eof))
	{
		free(str);
		return (2);
	}
	return (0);
}
