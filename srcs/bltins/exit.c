/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:33:25 by soemin            #+#    #+#             */
/*   Updated: 2025/09/22 18:33:26 by soemin           ###   ########.fr       */
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

void	exit_prompt(int code)
{
	char	*line;
	char	*home;

	while (1)
	{
		line = readline("");
		if (!line)
			exit(code);
		if (line[0] == '\0')
		{
			home = getenv("HOME");
			if (home && chdir(home) == -1)
				perror("cd");
			free(line);
			return ;
		}
		free(line);
	}
}

static int	validate_exit_args(char **args, int last_status, int *code)
{
	int	valid;

	if (!args[1])
		exit(last_status);
	if (!is_num(args[1]))
	{
		printf("logout\nexit: %s: numeric argument required\n\n", args[1]);
		printf("[process exited with code 2 (0x00000002)]\n");
		printf("You can now close minishell with Ctrl+D,");
		printf(" or press Enter to restart.\n");
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
	if (code != 0)
	{
		printf("logout\n\n");
		printf("[process exited with code %d (0x%08x)]\n", code, code);
		printf("You can now close minishell with Ctrl+D,");
		printf(" or press Enter to restart.\n");
		exit_prompt(code);
		return (-1);
	}
	exit(code);
}
