/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:43:46 by ksan              #+#    #+#             */
/*   Updated: 2025/10/13 16:02:17 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char	*strip_quotes(char *str)
{
	size_t	len;

	len = strlen(str);
	if (len >= 2)
	{
		if ((str[0] == '"' && str[len - 1] == '"')
			|| (str[0] == '\'' && str[len - 1] == '\''))
		{
			str[len - 1] = '\0';
			return (str + 1);
		}
	}
	return (str);
}

static void	update_quotes(char c, int *in_s, int *in_d)
{
	if (c == '\'' && !(*in_d))
		*in_s = !(*in_s);
	else if (c == '"' && !(*in_s))
		*in_d = !(*in_d);
}

static char	*malloc_token(const char *start, int len)
{
	char	*token;
	int		i;

	token = malloc(len + 1);
	if (!token)
		return (NULL);
	i = 0;
	while (i < len)
	{
		token[i] = start[i];
		i++;
	}
	token[len] = '\0';
	return (token);
}

static	char	*check_end(char *str)
{
	if (*str == '|')
		return (str + 1);
	else
		return (NULL);
}

char	*next_pipe_token(char *str)
{
	static char	*input = NULL;
	char		*start;
	int			len;
	int			in_s;
	int			in_d;

	if (str)
		input = str;
	if (!input || *input == '\0')
		return (NULL);
	start = input;
	in_s = 0;
	in_d = 0;
	len = 0;
	while (*input)
	{
		update_quotes(*input, &in_s, &in_d);
		if (*input == '|' && !in_s && !in_d)
			break ;
		input++;
		len++;
	}
	input = check_end(input);
	return (malloc_token(start, len));
}

/*
void	tokenize_and_print(char *cmd, int index)
{
	char	*token;

	printf("Command %d:\n", index);
	token = strtok(cmd, " \t\n");
	while (token)
	{
		token = strip_quotes(token);
		printf("  [%s]\n", token);
		token = strtok(NULL, " \t\n");
	}
}

int	main(void)
{
	char	input[] = "echo \"hello |\" | grep 'hello world' | wc -l";
	char	*segment;
	int		index;

	index = 0;
	segment = next_pipe_token(input);
	while (segment)
	{
		tokenize_and_print(segment, index);
		free(segment);
		index++;
		segment = next_pipe_token(NULL);
	}
	return (0);
}
*/
