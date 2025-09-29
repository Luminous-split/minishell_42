/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:33:25 by soemin            #+#    #+#             */
/*   Updated: 2025/09/29 17:50:10 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_num(const char *str)
{
	int	i;

	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	parse_exit_code(const char *str, int *valid)
{
	long	result;
	int		code;

	result = atol_valid(str, valid);
	code = (int)(result % 256);
	if (code < 0)
		code += 256;
	return (code);
}

static int	validate_exit_args(char **args, int last_status, int *code)
{
	int	valid;

	if (!args[1])
		exit(last_status);
	if (!is_num(args[1]))
	{
		exit_prompt(2);
		return (0);
	}
	if (args[2])
	{
		printf("logout\nexit: too many arguments\n");
		return (0);
	}
	*code = parse_exit_code(args[1], &valid);
	if (!valid)
	{
		printf("exit: %s: numeric argument required\n", args[1]);
		exit(2);
	}
	return (1);
}

int	ft_exit(char **args, int last_status)
{
	int	code;

	if (!validate_exit_args(args, last_status, &code))
		return (1);
	exit(code);
}
