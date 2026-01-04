/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 14:59:38 by soemin            #+#    #+#             */
/*   Updated: 2026/01/04 16:19:38 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	unquoted(char **tok, char *buf)
{
	if (!part)
		return (-1);
	if (append_str(tok, buf) == -1)
	{
		free(buf);
		return (-1);
	}
	free(buf);
	return (0);
}
