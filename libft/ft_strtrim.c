/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:12:11 by soemin            #+#    #+#             */
/*   Updated: 2025/05/08 22:30:20 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	start = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	return (ft_substr(s1, start, end - start));
}
/*
#include <stdio.h>
int main(void)
{
    const char *str1 = "   Hello, world!   ";
    const char *set1 = " ";
    char *result1 = ft_strtrim(str1, set1);
    printf("Test 1: ft_strtrim(\"%s\", \" \") = \"%s\"\n", str1, result1);
    return (0);
}
*/
