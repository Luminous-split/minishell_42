/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:13:53 by soemin            #+#    #+#             */
/*   Updated: 2025/05/08 22:17:41 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = b;
	i = 0;
	while (i < len)
		ptr[i++] = (unsigned char)c;
	return (b);
}
/*
#include <stdio.h>
int main(void)
{
    char str1[20] = "Hello, world!";
    printf("Before ft_memset: %s\n", str1);
    ft_memset(str1, 'X', 5);
    printf("After ft_memset (first 5 chars): %s\n\n", str1);
    char str2[20] = "Hello, world!";
    ft_memset(str2, 0, 5);  // Set first 5 chars to '\0'
    printf("After ft_memset (first 5 chars set to '\\0'): %s\n", str2);
    int arr[5] = {1, 2, 3, 4, 5};
    printf("\nBefore ft_memset on int array: ");
    for (int i = 0; i < 5; i++)
        printf("%d ", arr[i]);
    printf("\n");
    ft_memset(arr, 0, 3 * sizeof(int));
    printf("After ft_memset (first 3 ints set to 0): ");
    for (int i = 0; i < 5; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return (0);
}
*/
