/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:35:18 by soemin            #+#    #+#             */
/*   Updated: 2026/01/04 15:56:04 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*handle_double_quotes(const char *line, int i, char **envp, int last_status)
{
	int     start;
	char    *sub;
	char    *expanded;

	if (!line || line[i] != '"')
		return (NULL);
	i++;
	start = i;
	while (line[i] && line[i] != '"')
		i++;
	if (line[i] != '"')
		return (NULL);
	sub = ft_substr(line, start, i - start);
	if (!sub)
		return (NULL);
	expanded = expand_dollar(sub, envp, last_status);
	free(sub);
	if (!expanded)
		return (NULL);
	return (expanded);
}
