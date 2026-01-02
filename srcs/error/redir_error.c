/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 17:32:38 by ksan              #+#    #+#             */
/*   Updated: 2025/12/27 17:32:38 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_error(void)
{
	ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
	return (-1);
}
