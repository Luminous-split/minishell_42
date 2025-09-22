/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:58:57 by soemin            #+#    #+#             */
/*   Updated: 2025/05/08 21:55:33 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
/*
#include <stdio.h>
void print_bytes(const unsigned char *buf, size_t len) 
{
	size_t	i;
	for (i = 0; i < len; i++)
		printf("%02x ", buf[i]);
}

int	main(void)
{
	unsigned char buf1[10] = "abcdefghi";
	unsigned char buf2[10] = "abcdefghi";
	
	ft_bzero(buf1, 5);
    	bzero(buf2, 5);
    	printf("Test 1 (n=5):\nft_bzero: ");
    	print_bytes(buf1, 10);
    	printf("\nbzero   : ");
    	print_bytes(buf2, 10);
    	printf("\n\n");

    	unsigned char buf3[10] = "123456789";
    	unsigned char buf4[10] = "123456789";

    	ft_bzero(buf3, 0);
    	bzero(buf4, 0);
    	printf("Test 2 (n=0):\nft_bzero: ");
    	print_bytes(buf3, 10);
    	printf("\nbzero   : ");
    	print_bytes(buf4, 10);
    	printf("\n\n");

    	unsigned char buf5[10] = "XXXXXXXXX";
    	unsigned char buf6[10] = "XXXXXXXXX";

    	ft_bzero(buf5, 10);
    	bzero(buf6, 10);
    	printf("Test 3 (n=10):\nft_bzero: ");
    	print_bytes(buf5, 10);
    	printf("\nbzero   : ");
    	print_bytes(buf6, 10);
    	printf("\n");

    	return (0);

}
*/
