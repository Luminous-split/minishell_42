/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:11:23 by soemin            #+#    #+#             */
/*   Updated: 2025/05/08 22:34:28 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*res;
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return (NULL);
	res = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!res)
		return (NULL);
	while (s[i])
	{
		res[i] = f(i, s[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}
/*
#include <stdio.h>

char example_func(unsigned int i, char c)
{
    if (i % 2 == 0) 
    {
        if (c >= 'a' && c <= 'z') 
	{
            return (c - 32);
	} 
	else 
	{
            return (c);
        }
    } else 
    {
        return (c);
    }
}

int main(void)
{
    const char *str1 = "hello";
    char *result1 = ft_strmapi(str1, example_func);
    printf("Test 1: ft_strmapi(\"%s\") = \"%s\"\n", str1, result1);
    free(result1);
    return (0);
}
*/
