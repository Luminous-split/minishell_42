/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 14:36:47 by ksan              #+#    #+#             */
/*   Updated: 2026/01/10 14:36:47 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	append_char(char **tok, char c)
{
	size_t	len;
	char	*new;

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
	size_t	len;
	char	*new;

	if (!s)
		return (0);
	if (*tok)
		len = ft_strlen(*tok);
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

int	append_nstr(char **tok, const char *s, size_t n)
{
	char	*tmp;

	tmp = ft_substr(s, 0, n);
	if (!tmp)
		return (-1);
	if (append_str(tok, tmp) == -1)
		return (free(tmp), -1);
	free(tmp);
	return (0);
}
