/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:12:08 by soemin            #+#    #+#             */
/*   Updated: 2026/01/04 16:52:36 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	append_char(char **tok, char c)
{
	char	*new;
	size_t	len;
	
	if (*tok)
		len = ft_strlen(*tok);
	else
		len = 0;
	new = malloc(len + 2);
	if (!new)
		return (-1);
	if (*tok)
		ft_memcpy(new, *tok, len);
	new[len] = c;
	new[len + 1] = '\0';
	free(*tok);
	*tok = new;
	return (0);
}

int	append_str(char **tok, const char *s)
{
	size_t	s_len;
	size_t len;
	char	*new;

	if (!s)
		return (0);
	if (tok)
		len = ft_strlen(tok);
	else
		len = 0;
	s_len = ft_strlen(s);
	new = malloc(len + s_len + 1);
	if (!new)
		return (-1);
	if (*tok)
		ft_memcpy(new, *tok, len);
	ft_memcpy(new + len, s, s_len);
	new[len + s_len] = '\0';
	free(*tok);
	*tok = new;
	return (0);
}

int	expand_dollar_var(const char *line, int i, char **tok, char **envp)
{
	char var[256];
	int k;
	char *val;
	
	k = 0;
	while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
		var[k++] = line[i++];
	var[k] = '\0';
	val = get_env_var(envp, var);
	if (val && append_str(tok, val) == -1)
		return (-1);
	return (i);
}

int expand_dollar_qm(int i, char **tok, int last_status)
{
	char *s;
	
	s = ft_itoa(last_status);
	
	if (!s)
		return (-1);
	if (append_str(tok, s) == -1)
	{
		free(s);
		return (-1);
	}
	free(s);
	return (i + 1);
}

char	*expand_dollar(const char *line, char **envp, int last_status)
{
	char *tok;
	int i;
	
	tok = NULL;
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			i++;
			if (line[i] == '?')
				i = expand_dollar_qm(i, &tok, last_status);
			else
				i = expand_dollar_var(line, i, &tok, envp);
			if (i < 0)
				return (free(tok), NULL);
		}
		else
		{
			if (append_char(&tok, line[i++]) == -1)
				return (free(tok), NULL);
		}
	}
	return (tok);
}
