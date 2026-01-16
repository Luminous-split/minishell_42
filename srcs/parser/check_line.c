/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 13:15:50 by ksan              #+#    #+#             */
/*   Updated: 2026/01/10 13:15:50 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pending(char *line)
{
	int		t_len;
	char	*trimmed;

	trimmed = ft_strtrim(line, " ");
	t_len = ft_strlen(trimmed);
	if (t_len > 1 && trimmed[t_len - 1] == '|')
	{
		free(trimmed);
		return (1);
	}
	free(trimmed);
	return (0);
}

static	void	append_line(char **line, char *extra,
	int old_size, int new_size)
{
	*line = ft_realloc(*line, (old_size + 1) * sizeof(char), new_size + 1);
	ft_memcpy((*line) + old_size, " ", 1);
	ft_memcpy((*line) + old_size + 1, extra, ft_strlen(extra)+1);
}

void	handle_pending_pipe(char **line)
{
	char	*extra;
	size_t	new_size;
	size_t	old_size;

	old_size = ft_strlen(*line);
	extra = readline("> ");
	while (extra && (!extra[0] || check_pending(extra)))
	{
		if ((extra[0] != '\0'))
		{
			new_size = (old_size + ft_strlen(extra) + 1) * sizeof(char);
			append_line(line, extra, old_size, new_size);
			old_size = ft_strlen(*line);
			free(extra);
		}
		extra = readline("> ");
	}
	if (extra)
	{
		new_size = (old_size + ft_strlen(extra) + 1) * sizeof(char);
		append_line(line, extra, old_size, new_size);
		free(extra);
	}
}

int	is_invalid_line(char *line)
{
	char	*temp_ptr;
	char	*temp_ptr1;

	temp_ptr = next_token(line, "|");
	while (temp_ptr)
	{
		if (temp_ptr[0] == '\0')
		{
			free(temp_ptr);
			return (1);
		}
		temp_ptr1 = ft_strtrim(temp_ptr, " ");
		if (temp_ptr1[0] == 0)
		{
			free(temp_ptr);
			free(temp_ptr1);
			return (1);
		}
		free(temp_ptr1);
		free(temp_ptr);
		temp_ptr = next_token(NULL, "|");
	}
	return (0);
}
