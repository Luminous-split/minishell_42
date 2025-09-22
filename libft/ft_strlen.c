/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:11:17 by soemin            #+#    #+#             */
/*   Updated: 2025/05/08 22:28:41 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
/*
#include <stdio.h>
int main(void)
{
    const char *str1 = "Hello, World!";
    size_t len1 = ft_strlen(str1);
    printf("Test 1: Length of \"%s\" is %zu\n", str1, len1);
    return (0);
}
*/
