/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 17:32:38 by ksan              #+#    #+#             */
/*   Updated: 2025/12/27 17:32:38 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_file_error(char *file)
{
	if (ft_strlen(file) == 0)
		ft_putendl_fd("minishell:  : No such file or directory", 2);
	else
		perror(file);
	return (1);
}

int	redir_error(void)
{
	ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
	return (-1);
}

int	err_pipe(char *line)
{
	char	*temp_ptr;

	temp_ptr = ft_strtrim(line, " ");
	if (!(temp_ptr[0] == '\0'))
	{
		free(temp_ptr);
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (2);
	}
	free(temp_ptr);
	return (0);
}
