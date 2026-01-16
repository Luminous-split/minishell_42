/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lineutil.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 15:33:43 by ksan              #+#    #+#             */
/*   Updated: 2026/01/09 15:33:43 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_freesplit(char **arr, size_t i)
{
	while (i--)
		free(arr[i]);
	free(arr);
	return (NULL);
}

static int	cal_indiv_len(char const **s, int *in_s, int *in_d, char c)
{
	int	len;

	len = 0;
	while (**s != '\0' && (*in_s || *in_d || **s != c))
	{
		if (**s == '\'' && !*in_d)
			*in_s = !(*in_s);
		else if (**s == '"' && !(*in_s))
			*in_d = !(*in_d);
		(*s)++;
		len++;
	}
	return (len);
}

static char	*ft_word_split(char const *s, size_t length)
{
	char	*word;

	word = (char *)malloc((sizeof(char) * length) + 1);
	if (!word)
		return (NULL);
	ft_memcpy(word, s, length);
	word[length] = '\0';
	return (word);
}

char	**ft_insert_words(char **splitted, char const *s, char c)
{
	int			i;
	int			in_s;
	int			in_d;
	const char	*word;
	size_t		indiv_slen;

	i = 0;
	in_s = 0;
	in_d = 0;
	while (*s != '\0')
	{
		while (*s == c && !in_s && !in_d)
			s++;
		if (*s == '\0')
			break ;
		word = s;
		indiv_slen = cal_indiv_len(&s, &in_s, &in_d, c);
		splitted[i] = ft_word_split(word, indiv_slen);
		if (!splitted[i])
			return (ft_freesplit(splitted, i));
		i++;
	}
	return (splitted);
}
