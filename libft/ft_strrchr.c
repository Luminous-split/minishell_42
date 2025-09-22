/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:11:53 by soemin            #+#    #+#             */
/*   Updated: 2025/05/08 22:30:04 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*last;

	last = NULL;
	while (*s)
	{
		if (*s == (char)c)
			last = s;
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return ((char *)last);
}
/*
#include <stdio.h>
int main(void)
{
    const char *str1 = "Hello, world!";
    char *result1 = ft_strrchr(str1, 'o');
    printf("Test 1: ft_strrchr(\"%s\", 'o') = \"%s\"\n", str1, result1);
    return (0);
}
*/
