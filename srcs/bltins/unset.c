/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:58:18 by soemin            #+#    #+#             */
/*   Updated: 2026/01/11 18:50:33 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	match_env(const char *env_entry, const char *name)
{
	size_t	len;

	len = ft_strlen(name);
	return (ft_strncmp(env_entry, name, len) == 0 && env_entry[len] == '=');
}

static int	count_keep_env(char **envp, const char *varname)
{
	int	i;
	int	keep;

	i = 0;
	keep = 0;
	while (envp[i])
	{
		if (!match_env(envp[i], varname))
			keep++;
		i++;
	}
	return (keep);
}

static char	**build_new_env(char **envp, const char *varname, int keep)
{
	char	**new_env;
	int		i;
	int		j;

	new_env = malloc((keep + 1) * sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	j = 0;
	while (envp[i])
	{
		if (!match_env(envp[i], varname))
			new_env[j++] = envp[i];
		else
			free(envp[i]);
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}

static int	remove_env_var(char ***envp, const char *varname)
{
	int		keep;
	char	**new_env;

	keep = count_keep_env(*envp, varname);
	new_env = build_new_env(*envp, varname, keep);
	if (!new_env)
		return (1);
	free(*envp);
	*envp = new_env;
	return (0);
}

int	ft_unset(char **args, char ***envp)
{
	int	k;
	int	status;

	if (!args || !args[1])
		return (0);
	k = 1;
	status = 0;
	while (args[k])
	{
		if (remove_env_var(envp, args[k]) != 0)
			status = 1;
		k++;
	}
	return (status);
}
