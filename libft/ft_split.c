/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:09:13 by soemin            #+#    #+#             */
/*   Updated: 2025/05/08 22:21:57 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_word_count(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

char	*ft_strdup_range(const char *start, const char *end)
{
	return (ft_substr(start, 0, end - start));
}

void	ft_free_split(char **result, size_t i)
{
	while (i--)
		free(result[i]);
	free(result);
}

int	ft_extract_word(const char **s, char c, char **result, size_t i)
{
	const char	*start;

	start = *s;
	while (**s && **s != c)
		(*s)++;
	result[i] = ft_strdup_range(start, *s);
	if (!result[i])
	{
		ft_free_split(result, i);
		return (0);
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	size_t	word_count;
	char	**result;
	size_t	i;

	word_count = ft_word_count(s, c);
	result = (char **)malloc(sizeof(char *) * (word_count + 1));
	i = 0;
	if (!result)
		return (NULL);
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			if (!ft_extract_word(&s, c, result, i))
				return (NULL);
			i++;
		}
	}
	result[i] = NULL;
	return (result);
}
/*
#include <stdio.h>
int main(void)
{
    const char *str1 = "Hello world from ft_split";
    char **result1 = ft_split(str1, ' ');
    printf("Test 1: Split string by spaces:\n");
    for (size_t i = 0; result1[i] != NULL; i++)
        printf("Word %zu: %s\n", i + 1, result1[i]);
    ft_free_split(result1, 5);
    return (0);
}
*/
