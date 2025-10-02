/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:43:26 by soemin            #+#    #+#             */
/*   Updated: 2025/10/02 17:10:02 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*handle_single_quotes(const char *line, int start, char *tok)
{
	int	i;
	int	j;

	i = start;
	j = 0;
	if (line[i] == '\'')
		i++;
	while (line[i] && line[i] != '\'')
	{
		tok[j] = line[i];
		i++;
		j++;
	}
	if (line[i] == '\'')
		i++;
	tok[j] = '\0';
	return (tok);
}								
