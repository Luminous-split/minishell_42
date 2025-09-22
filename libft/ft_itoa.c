/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:03:12 by soemin            #+#    #+#             */
/*   Updated: 2025/05/08 21:58:52 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_len(long n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	nb;

	nb = (long)n;
	len = num_len(nb);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	len--;
	if (nb == 0)
		str[0] = '0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	while (nb)
	{
		str[len] = (nb % 10) + '0';
		nb /= 10;
		len--;
	}
	return (str);
}
/*
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
int main(void)
{
    char *s;

    s = ft_itoa(0);
    printf("ft_itoa(0) = %s\n", s);
    free(s);

    s = ft_itoa(123);
    printf("ft_itoa(123) = %s\n", s);
    free(s);

    s = ft_itoa(-123);
    printf("ft_itoa(-123) = %s\n", s);
    free(s);

    s = ft_itoa(1);
    printf("ft_itoa(1) = %s\n", s);
    free(s);

    s = ft_itoa(-1);
    printf("ft_itoa(-1) = %s\n", s);
    free(s);

    s = ft_itoa(2147483647);
    printf("ft_itoa(INT_MAX) = %s\n", s);
    free(s);

    s = ft_itoa(-2147483648);
    printf("ft_itoa(INT_MIN) = %s\n", s);
    free(s);

    s = ft_itoa(1000000);
    printf("ft_itoa(1000000) = %s\n", s);
    free(s);

    s = ft_itoa(-987654321);
    printf("ft_itoa(-987654321) = %s\n", s);
    free(s);

    return (0);
}
*/
