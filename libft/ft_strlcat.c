/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:10:15 by soemin            #+#    #+#             */
/*   Updated: 2025/05/08 22:27:56 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dlen;
	size_t	slen;
	size_t	i;

	dlen = 0;
	slen = ft_strlen(src);
	while (dlen < dstsize && dst[dlen])
		dlen++;
	if (dlen == dstsize)
		return (dstsize + slen);
	i = 0;
	while (src[i] && dlen + i < dstsize - 1)
	{
		dst[dlen + i] = src[i];
		i++;
	}
	if (dlen + i < dstsize)
		dst[dlen + i] = '\0';
	return (dlen + slen);
}
/*
#include <stdio.h>
int main(void)
{
    char dst1[20] = "Hello, ";
    const char *src1 = "World!";
    size_t dstsize1 = 20;
    size_t result1 = ft_strlcat(dst1, src1, dstsize1);
    printf("Test 1: After ft_strlcat: %s (result: %zu)\n", dst1, result1);
    return(0);
}
*/
