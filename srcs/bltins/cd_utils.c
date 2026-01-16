/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:42:22 by soemin            #+#    #+#             */
/*   Updated: 2026/01/11 19:02:34 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

char	*get_env_var(char **env, const char *name)
{
	size_t	len;
	int		i;

	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

void	set_env_var(char **env, const char *name, const char *value)
{
	size_t	len;
	size_t	total_len;
	char	*updated_var;
	int		i;

	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
		{
			total_len = len + 1 + ft_strlen(value) + 1;
			updated_var = malloc(total_len);
			if (!updated_var)
				return ;
			ft_strlcpy(updated_var, name, total_len);
			ft_strlcat(updated_var, "=", total_len);
			ft_strlcat(updated_var, value, total_len);
			free(env[i]);
			env[i] = updated_var;
			return ;
		}
		i++;
	}
}
