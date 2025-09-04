/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 18:52:25 by soemin            #+#    #+#             */
/*   Updated: 2025/09/04 18:53:16 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_env(char **args, char **envp)
{
	int	i;

	if (args && args[1])
	{
		write(2, "env: too many arguments\n", 24);
		return (1);
	}
	if (!envp || !*envp)
		return (0);
	i = 0;
	while (envp[i])
	{
		ft_putendl_fd(envp[i], 1);
		i++;
	}
	return (0);
}
