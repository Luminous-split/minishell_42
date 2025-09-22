/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:09:57 by soemin            #+#    #+#             */
/*   Updated: 2025/05/08 22:27:35 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, len1 + 1);
	ft_strlcpy(str + len1, s2, len2 + 1);
	return (str);
}
/*
#include <stdio.h>
int main(void)
{
    const char *str1 = "Hello, ";
    const char *str2 = "World!";
    char *result1 = ft_strjoin(str1, str2);
    if (result1)
    {
	printf("Test 1: Joined string: %s\n", result1);
        free(result1);
    }
    else
        printf("Test 1: Memory allocation failed\n");
    return (0);
}
*/
