/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:12:08 by soemin            #+#    #+#             */
/*   Updated: 2025/11/23 19:44:52 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	expand_dollar_var(const char *line, char *tok, char **envp, int i)
{
	int		j;
	int		k;
	char	var[256];
	char	*env_val;

	j = 0;
	k = 0;
	while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
	{
		var[k++] = line[i++];
	}
	var[k] = '\0';
	j = ft_strlen(tok);
	env_val = get_env_var(envp, var);
	if (env_val)
	{
		ft_strlcpy(&tok[j], env_val, 1024 - j);
	}
	return (i);
}

int	expand_dollar_qm(const char *line, char *tok, int last_status, int i)
{
	int	j;
	int	k;
	char	*exit_str;

	(void)line;
	exit_str = ft_itoa(last_status);
	if (!exit_str)
		return (i);
	j = 0;
	k = 0;
	while (exit_str[k])
		tok[j++] = exit_str[k++];
	free(exit_str);
	return (i + 1);
}

void	expand_dollar(const char *line, char *tok, char **envp, int last_status)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			i++;
			if (line[i] == '?') 
				i = expand_dollar_qm(line, tok + j, last_status, i);
			else
				i = expand_dollar_var(line, tok + j, envp, i);
			while (tok[j])
				j++;
		}
		else
			tok[j++] = line[i++];
	}
	tok[j] = '\0';
}
