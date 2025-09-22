/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 09:57:03 by soemin            #+#    #+#             */
/*   Updated: 2025/05/08 21:55:00 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res * sign);
}

/*
int	main(void)
{
    printf("%d, %d\n", ft_atoi("42"), atoi("42"));
    printf("%d, %d\n", ft_atoi("   42"), atoi("   42"));
    printf("%d, %d\n", ft_atoi("\t\n\v\f\r  -42"), atoi("\t\n\v\f\r  -42"));
    printf("%d, %d\n", ft_atoi("+42"), atoi("+42"));
    printf("%d, %d\n", ft_atoi("   +0042"), atoi("   +0042"));
    printf("%d, %d\n", ft_atoi("   -0042"), atoi("   -0042"));
    printf("%d, %d\n", ft_atoi("2147483647"), atoi("2147483647"));
    printf("%d, %d\n", ft_atoi("-2147483648"), atoi("-2147483648"));
    printf("%d, %d\n", ft_atoi("2147483648"), atoi("2147483648"));
    printf("%d, %d\n", ft_atoi("-2147483649"), atoi("-2147483649"));
    printf("%d, %d\n", ft_atoi("abc"), atoi("abc"));
    printf("%d, %d\n", ft_atoi("123abc"), atoi("123abc"));
    printf("%d, %d\n", ft_atoi("   -0012a42"), atoi("   -0012a42"));
    printf("%d, %d\n", ft_atoi(""), atoi(""));
 
    return (0);
}
*/
