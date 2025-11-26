/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:35:18 by soemin            #+#    #+#             */
/*   Updated: 2025/11/23 19:49:22 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*hand_dq(const char *line, int start, char **envp, int last_status)
{
	int		i;
	int		j;
	char	*tok;

	i = start;
	j = 0;
	tok = malloc(4096);
	if (!tok)
		return (NULL);
	if (line[i] == '"')
		i++;
	while (line[i] && line[i] != '"')
	{
		if (line[i] == '$')
		{
			expand_dollar(&line[i], tok + j, envp, last_status);
			if (line[i + 1] == '?')
				i += 2;
			else
			{
				i++;
				while (line[i] && (ft_isalnum(line[i]) || line[i] == '_' ))
					i++;
			}
			while (tok[j])
				j++;
		}
		else
			tok[j++] = line[i++];
	}
	if (line[i] == '"')
		i++;
	tok[j] = '\0';
	return (tok);
}
