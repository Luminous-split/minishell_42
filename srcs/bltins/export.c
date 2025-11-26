/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 19:46:45 by soemin            #+#    #+#             */
/*   Updated: 2025/11/23 17:06:14 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	is_valid_identifier(const char *name)
{
	const char	*p;

	p = name + 1;
	if (!name || !*name)
		return (0);
	if (!(ft_isalpha((unsigned char)name[0]) || name[0] == '_'))
		return (0);
	while (*p)
	{
		if (!(ft_isalnum((unsigned char)*p) || *p == '_'))
			return (0);
		p++;
	}
	return (1);
}

static int	parse_token(const char *token, char **name, const char **value)
{
	const char	*eq;
	size_t		name_len;

	eq = ft_strchr(token, '=');
	if (!eq)
		return (0);
	name_len = eq - token;
	if (name_len == 0)
		return (1);
	*name = ft_strndup(token, name_len);
	if (!*name)
	{
		perror("strndup");
		return (1);
	}
	*value = eq + 1;
	return (0);
}

static int	export_var(const char *token, char ***envp)
{
	char		*name;
	const char	*value;
	int			status;

	name = NULL;
	value = NULL;
	status = 0;
	if (parse_token(token, &name, &value) != 0)
		return (1);
	if (!name)
		return (0);
	if (!is_valid_identifier(name))
	{
		printf("minishell: export: '%s': is not a valid identifier", name);
		status = 1;
	}
	if (ft_setenv(envp, name, value) != 0)
	{
		perror("setenv");
		status = 1;
	}
	free(name);
	return (status);
}

int	ft_export(char **args, char ***envp, int *last_status)
{
	int		status;
	int		i;

	status = 0;
	if (!args[1])
	{
		i = 0;
		while ((*envp)[i])
		{
			printf("declare -x %s\n", (*envp)[i]);
			i++;
		}
		*last_status = 0;
		return (0);
	}
	i = 1;
	while (args[i])
	{
		if (export_var(args[i], envp) != 0)
			status = 1;
		i++;
	}
	*last_status = status;
	return (status);
}
