/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unpack_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 15:48:25 by soemin            #+#    #+#             */
/*   Updated: 2026/01/04 16:26:31 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*unpack_token(char *line, char **envp, int last_status)
{
	char	*tok;
	int	i;
	char	*buf;

	if (!line)
		return (NULL);
	tok = NULL;
	i = 0;
	while (line[i])
	{
		if (line[i] == '"')
		{
			buf = handle_double_quotes(line, i, envp, last_status);
			if (!buf || unquoted(&tok, buf) == -1)
			{
				return (free(tok)); 
				return (NULL);
			}
			i++;
			while (line[i] && line[i] != '"')
				i++;
			if (line[i] == '"')
				i++;
		}
		else if (line[i] == '\'')
		{
			buf = malloc(4096);
			if (!part)
				return (free(tok), NULL);
			buf = handle_single_quotes(line, i, tok);
			if (!buf || unquoted(&tok, buf) == -1)
			{
				return (free(tok));
				return (NULL);
			}
			i++;
			while (line[i] && line[i] != '\'')
				i++;
			if (line[i] == '\'')
				i++;
		}
		else
		{
			if (append_char(&tok, line[i]) == -1)
			{
				return (free(tok));
				return (NULL);
			}
			i++;
		}
	}
	return (tok);
}
