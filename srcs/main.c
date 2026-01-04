/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:48:34 by soemin            #+#    #+#             */
/*   Updated: 2026/01/04 14:02:24 by soemin           ###   ########.fr       */
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

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	cmds = NULL;
	cmd_count = 0;
	last_status = 0;
=======
=======
>>>>>>> ac95e40 (Implemented parsing for input)
//	cmds = NULL;
//	cmd_count = 0;
//	last_status = 0;
//	my_env = dup_env(envp);
<<<<<<< HEAD
>>>>>>> 76f4f06 (Editing Compilation Errors for some .c files)
=======
=======
	cmds = NULL;
	cmd_count = 0;
	last_status = 0;
>>>>>>> 8592728 (implemented parsing for input)
>>>>>>> ac95e40 (Implemented parsing for input)
=======
	cmds = NULL;
	cmd_count = 0;
	last_status = 0;
>>>>>>> 650d057 (fixed pipeline (heredoc not yet))
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
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
		cmd_count = prepare_cmds(cmds, line, envp);
		last_status = exec_and_get_status(cmds, cmd_count);
		parse_cleanup(cmds, cmd_count);
=======
=======
>>>>>>> ac95e40 (Implemented parsing for input)
=======
>>>>>>> 650d057 (fixed pipeline (heredoc not yet))
//		if (is_builtin(args))
//			run_builtin(args, &envp, last_status);
//		else
//			run_binary(args, my_env);
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> 76f4f06 (Editing Compilation Errors for some .c files)
=======
=======
		cmd_count = prepare_cmds(cmds, line, envp);
		last_status = exec_and_get_status(cmds, cmd_count);
		parse_cleanup(cmds, cmd_count);
>>>>>>> 8592728 (implemented parsing for input)
>>>>>>> ac95e40 (Implemented parsing for input)
=======
		cmd_count = prepare_cmds(&cmds, line, envp);
		last_status = exec_and_get_status(cmds, cmd_count);
//		parse_cleanup(cmds, cmd_count);
>>>>>>> 650d057 (fixed pipeline (heredoc not yet))
=======

//		handle_pending_pipe(&line);
		printf("%s\n", line);
<<<<<<< HEAD
<<<<<<< HEAD
//		if (prepare_cmds(&cmds, line, envp, &cmd_count) != -1)
		//last_status = 
		(void)exec_and_get_status;
		//(cmds, cmd_count);
>>>>>>> 6895981 (fixed return values for invalid command cases)
=======
		if (prepare_cmds(&cmds, line, envp, &cmd_count) != -1)
		last_status = exec_and_get_status(cmds, cmd_count);
>>>>>>> 164440c (added valgrind test)
=======
		if (prepare_cmds(&cmds, line, envp, (int *[]){&cmd_count, &last_status}) != -1)
			last_status = exec_and_get_status(cmds, cmd_count);
>>>>>>> 25131b7 (edits on heredocs and tokens)
		free(line);
	}
	return (0);
}
