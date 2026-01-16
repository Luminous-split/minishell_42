/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 19:46:45 by soemin            #+#    #+#             */
/*   Updated: 2026/01/15 15:57:59 by ksan             ###   ########.sg       */
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

static int	parse_token(const char *token, char **name, char **value)
{
	size_t		name_len;
	const char	*eq;

	eq = ft_strchr(token, '=');
	if (!eq)
	{
		*name = ft_strdup(token);
		*value = ft_strdup("");
		if (*name && *value)
			return (0);
		free(*name);
		free(*value);
		return (1);
	}
	name_len = eq - token;
	if (name_len == 0)
		return (1);
	*name = ft_strndup(token, name_len);
	*value = ft_strdup(eq + 1);
	if (*name && *value)
		return (0);
	free(*name);
	free(*value);
	return (1);
}

static int	apply_export(char ***envp, char *name, char *value)
{
	if (value == NULL)
		return (0);
	if (ft_setenv(envp, name, value) != 0)
	{
		perror("setenv");
		return (1);
	}
	return (0);
}

static int	export_var(const char *token, char ***envp)
{
	int		status;
	char	*name;
	char	*value;

	status = 0;
	name = NULL;
	value = NULL;
	if (parse_token(token, &name, &value) != 0)
		return (1);
	if (!name)
		return (0);
	if (!name || *name == '\0' || !is_valid_identifier(name))
	{
		write(2, "minishell: export: `", 20);
		write(2, token, ft_strlen(token));
		write(2, "': not a valid identifier\n", 26);
		free(name);
		return (1);
	}
	if (name)
		status = apply_export(envp, name, value);
	free(name);
	free(value);
	return (status);
}

int	ft_export(char **args, char ***envp, int *last_status)
{
	int		i;
	int		status;

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
