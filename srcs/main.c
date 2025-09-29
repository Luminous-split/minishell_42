/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:48:34 by soemin            #+#    #+#             */
/*   Updated: 2025/09/29 15:52:29 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*line;
	char 	**args;
	int	last_status;

	(void)ac;
	(void)av;
	(void)envp;
	last_status = 0;
	ft_putstr_fd("Hello", 1);
}
