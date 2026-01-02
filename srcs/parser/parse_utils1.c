/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:43:46 by ksan              #+#    #+#             */
/*   Updated: 2025/10/13 16:02:17 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_quotes(char c, int *in_s, int *in_d)
{
	if (c == '\'' && !(*in_d))
		*in_s = !(*in_s);
	else if (c == '"' && !(*in_s))
		*in_d = !(*in_d);
}

static char	*malloc_token(const char *start, int len)
{
	char	*token;
	int		i;

	token = malloc(len + 1);
	if (!token)
		return (NULL);
	i = 0;
	while (i < len)
	{
		token[i] = start[i];
		i++;
	}
	token[len] = '\0';
	return (token);
}

static	char	*check_end(char *str, char *delim)
{
	int	delim_len;

	delim_len = ft_strlen(delim);
	if (ft_strncmp(str, delim, delim_len) == 0)
		return (str + delim_len);
	else
		return (NULL);
}

char	*next_token(char *str, char *delim)
{
	static char	*input;
	char		*start;
	int			len;
	int			in_s;
	int			in_d;

	if (str)
		input = str;
	if (!input || *input == '\0')
		return (NULL);
	start = input;
	in_s = 0;
	in_d = 0;
	len = 0;
	while (*input)
	{
		update_quotes(*input, &in_s, &in_d);
		if (ft_strnstr(input, delim, ft_strlen(delim)) && !in_s && !in_d)
			break ;
		input++;
		len++;
	}
	input = check_end(input, delim);
	return (malloc_token(start, len));
}
