/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:33:25 by soemin            #+#    #+#             */
/*   Updated: 2026/01/12 12:53:30 by soemin           ###   ########.fr       */
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
	{
		*code = last_status;
		return (1);
	}
	if (!is_num(args[1]))
	{
		write(2, "minishell: exit: numeric argument required\n", 43);
		*code = 2;
		return (1);
	}
	if (args[2])
	{
		write(2, "minshell: exit: too many arguments\n", 36);
		return (0);
	}
	*code = parse_exit_code(args[1], &valid);
	if (!valid)
	{
		*code = 2;
		return (1);
	}
	return (1);
}

int	ft_exit(t_list_cmds *cmd, char ***ep, int *vars, int track_fds)
{
	int	code;
	int	i;

	i = -1;
	if (!validate_exit_args(cmd->args, vars[0], &code))
		return (1);
	write(2, "exit\n", 5);
	exit_cleanup_vars(cmd, ep, track_fds);
	exit(code);
}
