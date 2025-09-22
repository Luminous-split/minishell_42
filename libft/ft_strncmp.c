/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:11:31 by soemin            #+#    #+#             */
/*   Updated: 2025/05/08 22:29:31 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n && *s1 && *s1 == *s2)
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
/*
#include <stdio.h>
int main(void)
{
    const char *str1 = "Hello";
    const char *str2 = "Hello";
    int result1 = ft_strncmp(str1, str2, 5);
    printf("Test 1: ft_strncmp(\"%s\", \"%s\", 5) = %d\n", str1, str2, result1);
    return (0);
}
*/
