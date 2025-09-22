/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:09:46 by soemin            #+#    #+#             */
/*   Updated: 2025/05/08 22:26:48 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/*
void print_char_with_index(unsigned int index, char *c)
{
    printf("Index: %u, Character: %c\n", index, *c);
}

int main(void)
{
    char str1[] = "Hello, World!";
    ft_striteri(str1, print_char_with_index);
    return (0);
}
*/
