/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:07:17 by soemin            #+#    #+#             */
/*   Updated: 2025/05/08 22:10:34 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*p1;
	unsigned char	*p2;

	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	while (n--)
	{
		if (*p1 != *p2)
			return (*p1 - *p2);
		p1++;
		p2++;
	}
	return (0);
}
/*
#include <stdio.h>
int main(void)
{
    char str1[] = "Hello, world!";
    char str2[] = "Hello, World!";
    char str3[] = "Hello, world!";
    int result = ft_memcmp(str1, str2, sizeof(str1));
    if (result == 0)
        printf("str1 and str2 are equal.\n");
    else
        printf("str1 and str2 are different. Result: %d\n", result);
    result = ft_memcmp(str1, str3, sizeof(str1));
    if (result == 0)
        printf("str1 and str3 are equal.\n");
    else
        printf("str1 and str3 are different. Result: %d\n", result);
    result = ft_memcmp(str1, str2, 5);  // Only compare the first 5 characters
    if (result == 0)
        printf("First 5 characters of str1 and str2 are equal.\n");
    else
        printf(" Result: %d\n", result);
    return (0);
}
*/
