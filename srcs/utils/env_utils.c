/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:26:34 by soemin            #+#    #+#             */
/*   Updated: 2026/01/06 15:24:31 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	append_env(char ***envp, char *new_entry)
{
	int		count;
	char	**tmp;

	count = 0;
	while ((*envp)[count])
		count++;
	tmp = ft_realloc(*envp, sizeof(char *) * count,
			sizeof(char *) * (count + 2));
	if (!tmp)
	{
		free(new_entry);
		return (1);
	}
	*envp = tmp;
	(*envp)[count] = new_entry;
	(*envp)[count + 1] = NULL;
	return (0);
}

static char	*make_env_entry(const char *name, const char *value)
{
	size_t	len_name;
	size_t	len_value;
	char	*entry;

	len_name = ft_strlen(name);
	len_value = ft_strlen(value);
	entry = malloc(len_name + len_value + 2);
	if (!entry)
		return (NULL);
	ft_strlcpy(entry, name, len_name + 1);
	entry[len_name] = '=';
	ft_strlcpy(entry + len_name + 1, value, len_value + 1);
	return (entry);
}

int	ft_setenv(char ***envp, const char *name, const char *value)
{
	char	*new_entry;
	int		i;
	size_t	len_name;

	new_entry = make_env_entry(name, value);
	if (!new_entry)
		return (1);
	i = 0;
	len_name = ft_strlen(name);
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], name, len_name) == 0
				&& (*envp)[i][len_name] == '=')
		{
			free((*envp)[i]);
			(*envp)[i] = new_entry;
			return (0);
		}
		i++;
	}
	return (append_env(envp, new_entry));
}

char	*get_path_value(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	**dup_env(char **envp)
{
	int		count;
	char	**cpy;
	int		i;

	count = 0;
	while (envp[count])
		count++;
	cpy = malloc((count + 1) * sizeof(char *));
	if (!cpy)
		return (NULL);
	i = 0;
	while (i < count)
	{
		cpy[i] = ft_strdup(envp[i]);
		if (!cpy[i])
		{
			while (--i >= 0)
				free(cpy[i]);
			free(cpy);
			return (NULL);
		}
		i++;
	}
	cpy[count] = NULL;
	return (cpy);
}
