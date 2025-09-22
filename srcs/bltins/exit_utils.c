/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:33:37 by soemin            #+#    #+#             */
/*   Updated: 2025/09/22 18:33:39 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_sign(const char *str, int *sign, int *valid)
{
	int	i;

	i = 0;
	*sign = 1;
	*valid = 1;
	if (!str)
	{
		*valid = 0;
		return (0);
	}
	if (str[0] == '+')
		i++;
	else if (str[0] == '-')
	{
		*sign = -1;
		i++;
	}
	return (i);
}

long	atol_valid(const char *str, int *valid)
{
	unsigned long	result;
	int				sign;
	int				i;

	result = 0;
	i = parse_sign(str, &sign, valid);
	if (!*valid)
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			*valid = 0;
			return (0);
		}
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
