/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:07:27 by soemin            #+#    #+#             */
/*   Updated: 2025/05/08 22:12:32 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	d = dst;
	s = src;
	if (!dst && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
/*
#include <stdio.h>
int main(void)
{
    // Test data
    char src[] = "Hello, world!";
    char dst[50];     
    ft_memcpy(dst, src, 5);
    dst[5] = '\0';
    printf("Source: %s\n", src);
    printf("Destination after ft_memcpy: %s\n", dst);
    ft_memcpy(src + 7, src, 5);
    printf("Source after memcpy (overlap test): %s\n", src);
    return (0);
}
*/
