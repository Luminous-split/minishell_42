/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:09:23 by soemin            #+#    #+#             */
/*   Updated: 2025/05/08 22:23:37 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}
/*
#include <stdio.h>
int main(void)
{
    const char *str1 = "Hello, World!";
    char *result1 = ft_strchr(str1, 'W');
    if (result1)
        printf("Test 1: Found 'W' at position: %ld\n", result1 - str1);
    else
        printf("Test 1: 'W' not found.\n");
    return (0);
}
*/
