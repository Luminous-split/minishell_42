/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:38:24 by soemin            #+#    #+#             */
/*   Updated: 2025/09/29 17:45:43 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*saveptr;
	char		*tok;

	if (str != NULL)
		saveptr = str;
	if (saveptr == NULL)
		return (NULL);
	while (*saveptr && strchr(delim, *saveptr))
		saveptr++;
	if (*saveptr == '\0')
		saveptr = NULL;
	tok = saveptr;
	while (*saveptr && !strchr(delim, *saveptr))
		saveptr++;
	if (*saveptr)
	{
		*saveptr = '\0';
		saveptr++;
	}
	else
		saveptr = NULL;
	return (tok);
}
