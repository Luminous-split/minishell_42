/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:12:08 by soemin            #+#    #+#             */
/*   Updated: 2026/01/12 12:58:06 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	expand_dollar_var(const char *line, int i, char **tok, char **envp)
{
	int		start;
	char	*key;
	char	*value;

	start = i;
	while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
		i++;
	key = ft_substr(line, start, i - start);
	if (!key)
		return (-1);
	value = get_env_var(envp, key);
	free(key);
	if (!value)
		value = ft_strdup("");
	else
		value = ft_strdup(value);
	if (!value)
		return (-1);
	if (append_str(tok, value) == -1)
	{
		free(value);
		return (-1);
	}
	free(value);
	return (i - start + 1);
}

int	expand_dollar_qm(char **tok, int last_status)
{
	char	*s;

	s = ft_itoa(last_status);
	if (!s)
		return (-1);
	if (append_str(tok, s) == -1)
	{
		free(s);
		return (-1);
	}
	free(s);
	return (2);
}

int	handle_dollar(char **tok, const char *line, char **envp, int last_status)
{
	int	i;

	i = 1;
	if (line[i] == '?')
	{
		expand_dollar_qm(tok, last_status);
		return (2);
	}
	else if (ft_isalpha(line[i]) || line[i] == '_')
		return (expand_dollar_var(line, i, tok, envp));
	else
	{
		append_char(tok, '$');
		return (1);
	}
}

char	*expand_dollar(const char *line, char **envp, int last_status)
{
	char	*tok;
	int		i;
	int		skip;

	tok = ft_strdup("");
	if (!tok)
		return (NULL);
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			skip = handle_dollar(&tok, line + i, envp, last_status);
			if (skip == -1)
				return (free(tok), NULL);
			i += skip;
		}
		else
		{
			if (append_char(&tok, line[i]) == -1)
				return (free(tok), NULL);
			i++;
		}
	}
	return (tok);
}
