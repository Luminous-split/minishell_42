/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:38:24 by soemin            #+#    #+#             */
/*   Updated: 2025/09/29 17:45:43 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*saveptr;
	char		*tok;
	char		*temp;
	int		index;

	if (str != NULL)
		saveptr = str;
	if (saveptr == NULL)
		return (NULL);
	temp = strstr(saveptr, delim);
	if (temp)
	{
		index = temp - saveptr;
		memset(temp, '\0', strlen(delim));
		tok = saveptr;
		saveptr = temp + strlen(delim);
		if (*saveptr  == '\0')
			saveptr = NULL;
	}
	else
	{
		tok = saveptr;
		saveptr = NULL;
	}
	return (tok);
}

/*
int	main()
{
	char str[] = "export name=soemin";

	char *out = ft_strtok(str, "=");
	while (out)
	{
		printf("%s\n", out);
		out = ft_strtok(NULL, "=");
	}
}
*/
