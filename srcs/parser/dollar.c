/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:12:08 by soemin            #+#    #+#             */
/*   Updated: 2025/10/02 16:31:22 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	expand_dollar_var(const char *line, char *tok, char **envp, int i)
{
	int		j;
	int		k;
	char	*var[256];
	char	*env_val;

	j = 0;
	k = 0;
	while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
	{
		var[k] = line[i];
		k++;
		i++;
	}
	var[k] = '\0';
	env_val = get_env_value(var, envp);
	if (env_val)
	{
		ft_strcpy(&tok[j], env_val);
		j += ft_strlen(env_val);
	}
	return (i);
}

int	expand_dollar_qm(const char *line, char *tok, int last_status, int i)
{
	int	j;
	char	*exit[256];
	int	k;

	j = 0;
	ft_itoa(last_status, exit);
	k = 0;
	while (exit[k])
		tok[j++] = exit[k++];
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
