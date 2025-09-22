/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:58:18 by soemin            #+#    #+#             */
/*   Updated: 2025/09/22 19:10:22 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	match_env(const char *env_entry, const char *name)
{
	size_t	len;

	len = strlen(name);
	return (strncmp(env_entry, name, len) == 0 && env_entry[len] == '=');
}

int	ft_unset(char **args, char *var_name)
{
	int		k;
	int		keep;
	int		i;
	char	**new_env;
	int		j;

	if (!args || !args[1])
		return (1);
	k = 1;
	while (args[k])
	{
		varname = args[k];
		keep = 0;
		i = 0;
		while (environ[i])
		{
			if (!match_env(environ[i], varname))
				keep++;
			i++;
		}
		*new_env = malloc((keep + 1) * sizeof(char *));
		if (!new_env)
			return (1);
		j = 0;
		i = 0;
		while (environ[i])
		{
			if (!match_env(environ[i], varname))
				new_env[j++] = environ[i];
			else
				free(environ[i]);
			i++;
		}
		new_env[j] = NULL;
		environ = new_env;
		k++;
	}
	return (0);
}
