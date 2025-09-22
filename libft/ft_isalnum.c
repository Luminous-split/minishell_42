/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:01:29 by soemin            #+#    #+#             */
/*   Updated: 2025/05/07 22:33:24 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}
/*
#include <stdio.h>
int	main(void)
{
	int c = 2;
	int res1 = ft_isalnum(c);
	printf("%d\n", res1);
	int d = 'd';
	int res2 = ft_isalnum(d);
	printf("%d\n", res2);
}
*/
