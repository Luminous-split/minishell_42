/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 07:27:31 by soemin            #+#    #+#             */
/*   Updated: 2026/01/11 11:51:34 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_shlvl(char **envp)
{
	int	i;
	int	lvl;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
		{
			if (envp[i][6] == '\0')
				return (0);
			if (!ft_isdigit(envp[i][6]) && envp[i][6] != '+')
				return (0);
			lvl = ft_atoi(envp[i] + 6);
			if (lvl < 0)
				return (0);
			return (lvl);
		}
		i++;
	}
	return (0);
}

void	update_shlvl(char ***envp)
{
	int		lvl;
	char	*lvlc;

	lvl = get_shlvl(*envp);
	if (lvl < 0)
		lvl = 0;
	lvl++;
	lvlc = ft_itoa(lvl);
	if (!lvlc)
		return ;
	ft_setenv(envp, "SHLVL", lvlc);
	free(lvlc);
}
