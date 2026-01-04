/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:48:34 by soemin            #+#    #+#             */
/*   Updated: 2025/11/26 18:17:35 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t g_signal = 0;

/*
static int	check_pending(char *line)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, " ");
	if (trimmed[ft_strlen(trimmed) - 1] == '|')
		return (1);
	free(trimmed);
	return (0);
}

static	void	handle_pending_pipe(char **line)
{
	char	*extra;
	size_t	new_size;
	size_t	old_size;

	old_size = ft_strlen(*line);
	if (check_pending(*line))
	{
		extra = readline("> ");
		while ((extra && extra[0] == '\0' ) || check_pending(extra))
		{
			if (!(extra[0] == '\0'))
			{
				new_size = (old_size + ft_strlen(extra)) * sizeof(char);
				*line = ft_realloc(*line, old_size * sizeof(char), new_size);
				ft_memcpy((*line)+old_size, extra, ft_strlen(extra));
				free(extra);
			}
			extra = readline("> ");
		}
	}
}
*/

int	main(int ac, char **av, char **envp)
{
	char	*line;
	int		last_status;
//	char	**my_env;
	t_list_cmds	*cmds;
	int	cmd_count;

	(void)ac;
	(void)av;
	(void)envp;

	cmds = NULL;
	cmd_count = 0;
	last_status = 0;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line)
			add_history(line);

//		handle_pending_pipe(&line);
		printf("%s\n", line);
		if (prepare_cmds(&cmds, line, envp, &cmd_count) != -1)
		last_status = exec_and_get_status(cmds, cmd_count);
		free(line);
	}
	return (0);
}
