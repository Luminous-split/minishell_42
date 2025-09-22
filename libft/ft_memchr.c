/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:07:08 by soemin            #+#    #+#             */
/*   Updated: 2025/05/08 22:08:13 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	while (n--)
	{
		if (*p == (unsigned char)c)
			return ((void *)p);
		p++;
	}
	return (NULL);
}
/*
#include <stdio.h>
int main(void)
{
    char str[] = "Hello, world!";
    char *result = ft_memchr(str, 'o', sizeof(str) - 1);
    if (result)
        printf("Found character 'o' at position: %ld\n", result - str);
    else
        printf("Character 'o' not found.\n");
    return (0);
}
*/
