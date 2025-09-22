/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:59:19 by soemin            #+#    #+#             */
/*   Updated: 2025/05/08 21:57:14 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (size && nmemb > SIZE_MAX / size)
		return (NULL);
	mem = malloc(nmemb * size);
	if (!mem)
		return (NULL);
	ft_bzero(mem, nmemb * size);
	return (mem);
}
/*
int	main(void) 
{
    size_t count = 5;
    size_t size = sizeof(int);

    int *arr1 = (int *)ft_calloc(count, size);
    int *arr2 = (int *)calloc(count, size);

    printf("ft_calloc: ");
    size_t i = 0;
    while (i < count)
    {
        printf("%d ", arr1[i]);
	i++;
    }
    printf("\n");

    printf("calloc   : ");
    size_t i = 0;
    while (i < count) 
    {
        printf("%d ", arr2[i]);
	i++;
    }
    printf("\n");

    free(arr1);
    free(arr2);

    return 0;
}
*/
