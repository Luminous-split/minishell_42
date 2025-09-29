/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 19:46:45 by soemin            #+#    #+#             */
/*   Updated: 2025/09/29 15:36:38 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	is_valid_identifier(const char *name)
{
	const char	*p;

	p = name + 1;
	if (!name || !*name)
		return (0);
	if (!(isalpha((unsigned char)name[0]) || name[0] == '_'))
		return (0);
	while (*p)
	{
		if (!(isalnum((unsigned char)*p) || *p == '_'))
			return (0);
		p++;
	}
	return (1);
}

static int	export_var(const char *token)
{
	const char	*eq;
	size_t		name_len;
	char		*name;
	const char	*value;

	eq = ft_strchr(token, '=');
	if (!eq)
		return (0);
	name_len = eq - token;
	if (name_len == 0)
		return (1);
	name = ft_strndup(token, name_len);
	if (!name)
	{
		perror("strndup");
		return (1);
	}
	value = eq + 1;
	if (!is_valid_identifier(name))
	{
		free(name);
		return (1);
	}
	if (set_env_var(name, value, 1) != 0)
	{
		perror("setenv");
		free(name);
		return (1);
	}
	free(name);
	return (0);
}

int	ft_export(char **args, int *last_status)
{
	int		status;
	int		i;
	char	**e;

	status = 0;
	if (!args[1])
	{
		*e = environ;
		while (e && *e)
		{
			printf("declare -x %s\n", *e);
			return (0);
		}
	}
	i = 1;
	while (args[i])
	{
		if (export_var(args[i]) != 0)
			status = 1;
		i++;
	}
	last_status = status;
	return (status);
}
