/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 15:12:59 by ksan              #+#    #+#             */
/*   Updated: 2026/01/09 15:13:05 by ksan             ###   ########.sg       */
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

static int	ft_count_words(char const *s, char c)
{
	int	count;
	int	i;
	int	is_in_word;
	int	in_s;
	int	in_d;

	i = 0;
	in_s = 0;
	in_d = 0;
	count = 0;
	is_in_word = 0;
	while (s[i] != '\0')
	{
		update_quotes(s[i], &in_s, &in_d);
		if (s[i] == c && !in_s && !in_d)
			is_in_word = 0;
		else if (!is_in_word)
		{
			is_in_word = 1;
			count++;
		}
		i++;
	}
	return (count);
}

char	**split_line(char const *s, char c)
{
	char		**splitted;
	int			wc;

	if (!s)
		return (NULL);
	wc = ft_count_words(s, c);
	splitted = (char **)malloc(sizeof(char *) * (wc + 1));
	if (!splitted)
		return (NULL);
	splitted[wc] = (NULL);
	splitted = ft_insert_words(splitted, s, c);
	return (splitted);
}
