/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:34:46 by ksan              #+#    #+#             */
/*   Updated: 2025/09/29 16:40:50 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_line(char *line)
{
	char **cmds;

	cmds = NULL;
	if (ft_strtok("", "|"))
		pass ;
	else
		cmds = ft_split(line, " ");
	return cmds;
}
