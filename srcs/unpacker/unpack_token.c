/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unpack_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 15:48:25 by soemin            #+#    #+#             */
/*   Updated: 2026/01/12 12:59:37 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	unpack_dq(char **tok, const char *line, char **envp, int last_status)
{
	int		i;
	int		start;
	char	*sub;
	char	*exp;

	i = 0;
	i++;
	start = i;
	while (line[i] && line[i] != '"')
		i++;
	sub = ft_substr(line, start, i - start);
	if (!sub)
		return (-1);
	exp = expand_dollar(sub, envp, last_status);
	free(sub);
	if (!exp || append_str(tok, exp) == -1)
		return (free(exp), -1);
	free(exp);
	if (line[i] == '"')
		i++;
	return (i);
}

int	unpack_quotes(char **tok, const char *line, char **envp, int last_status)
{
	int	i;

	if (!line || !tok)
		return (-1);
	if (line[0] == '\'')
	{
		i = 1;
		while (line[i] && line[i] != '\'')
			i++;
		if (append_nstr(tok, line + 1, i - 1) == -1)
			return (free(tok), -1);
		if (line[i] == '\'')
			i++;
		return (i);
	}
	else if (line[0] == '"')
		return (unpack_dq(tok, line, envp, last_status));
	return (-1);
}

int	unpack_both(char **tok, char *line, char **envp, int last_status)
{
	if (*line == '\'' || *line == '"')
		return (unpack_quotes(tok, line, envp, last_status));
	if (*line == '$')
		return (handle_dollar(tok, line, envp, last_status));
	return (0);
}

char	*unpack_token(char *line, char **envp, int last_status)
{
	char	*tok;
	int		i;
	int		skip;

	i = 0;
	tok = NULL;
	while (line[i])
	{
		skip = unpack_both(&tok, line + i, envp, last_status);
		if (skip == -1)
			return (free(tok), NULL);
		if (skip > 0)
			i += skip;
		else
		{
			if (append_char(&tok, line[i]) == -1)
				return (free(tok), NULL);
			i++;
		}
	}
	return (tok);
}
