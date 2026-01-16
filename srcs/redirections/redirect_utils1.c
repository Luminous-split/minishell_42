/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 19:14:34 by ksan              #+#    #+#             */
/*   Updated: 2025/12/27 19:14:34 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_cmdlet_count(char **cmd_arr)
{
	int	count;

	count = 0;
	while (cmd_arr[count])
		count++;
	return (count);
}

int	is_redir_char(char *arg)
{
	if (ft_strlen(arg) == 1 && ft_strncmp(arg, ">", 1) == 0)
		return (1);
	return (0);
}

int	is_append_char(char *arg)
{
	if (!arg)
		return (0);
	if (ft_strlen(arg) == 2 && ft_strncmp(arg, ">>", 2) == 0)
		return (1);
	return (0);
}

int	is_inredirect_char(char *arg)
{
	if (!arg)
		return (0);
	if (ft_strlen(arg) == 1 && ft_strncmp(arg, "<", 1) == 0)
		return (1);
	return (0);
}

int	is_heredoc_char(char *arg)
{
	if (!arg)
		return (0);
	if (ft_strlen(arg) == 2 && ft_strncmp(arg, "<<", 2) == 0)
		return (1);
	return (0);
}
