/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 14:59:38 by soemin            #+#    #+#             */
/*   Updated: 2026/01/04 15:01:02 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	unquoted(char **tok, char *part)
{
	if (!part)
		return (-1);
	if (append_str(tok, part) == -1)
	{
		free(part);
		return (-1);
	}
	free(part);
	return (0);
}
