/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:09:33 by soemin            #+#    #+#             */
/*   Updated: 2025/05/08 22:26:07 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	size_t	len;
	char	*dup;
	size_t	i;

	len = 0;
	i = 0;
	while (src[len])
		len++;
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	while (i <= len)
	{
		dup[i] = src[i];
		i++;
	}
	return (dup);
}
/*
#include <stdio.h>
int main(void)
{
    const char *str1 = "Hello, World!";
    char *dup1 = ft_strdup(str1);
    if (dup1)
    {
        printf("Test 1: Duplicated string: %s\n", dup1);
        free(dup1);
    }
    else
        printf("Test 1: Memory allocation failed\n");
    return (0);
}
*/
