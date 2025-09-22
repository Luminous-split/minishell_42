/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:13:46 by soemin            #+#    #+#             */
/*   Updated: 2025/05/08 22:15:37 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	if (!dest && !src)
		return (NULL);
	d = dest;
	s = src;
	if (s < d)
	{
		i = len;
		while (i-- > 0)
			d[i] = s[i];
	}
	else
	{
		i = 0;
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}
/*
#include <stdio.h>
int main(void)
{
    char src1[] = "Hello, world!";
    char dest1[50];
    ft_memmove(dest1, src1, 5);
    dest1[5] = '\0';
    printf("Test 1 (non-overlapping):\n");
    printf("Source: %s\n", src1);
    printf("Destination after ft_memmove: %s\n\n", dest1);
    char src2[] = "Hello, world!";
    ft_memmove(src2 + 7, src2, 5);
    printf("Test 2 (overlapping):\n");
    printf("Source after ft_memmove (overlap test): %s\n\n", src2);
    char src3[] = "This is a test!";
    ft_memmove(src3, src3, 4);
    printf("Test 3 (same source and destination):\n");
    printf("Source after ft_memmove (same): %s\n\n", src3);
    return (0);
}
*/
