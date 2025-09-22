/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:10:26 by soemin            #+#    #+#             */
/*   Updated: 2025/05/08 22:28:26 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (i < dstsize - 1 && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}
/*
#include <stdio.h>
int main(void)
{
    char dst1[20];
    const char *src1 = "Hello, World!";
    size_t dstsize1 = 20;
    size_t result1 = ft_strlcpy(dst1, src1, dstsize1);
    printf("Test 1: Copied string: %s (result: %zu)\n", dst1, result1);
    return (0);
}
*/
