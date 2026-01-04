/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:34:46 by ksan              #+#    #+#             */
/*   Updated: 2025/10/02 18:54:53 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		printf("[%s]", args[i]);
		i++;
	}
}

static void	info_printpipetokens(t_list_cmds *cmds, int count)
{
	int	i;
	int	j;

	i = -1;
	while (++i < count)
	{
		j = -1;
		printf("\n--------------CMD: %d { Total : %d }--------\n", i + 1, count);
		printf("Is Builtin: [%d]\n", cmds[i].bltin);
		printf("Filename append: [%s]\n", cmds[i].file_toappend);
		printf("Filename infile: [%s]\n", cmds[i].file_toread);
		printf("All Eof: ");
		if (cmds[i].all_eof != NULL)
		{
			while (cmds[i].all_eof[++j])
				printf("[%s]", cmds[i].all_eof[j]);
			printf("\n");
		}
		else
			printf("No Eof\n");
		printf("Chosen Eof: %s\n", cmds[i].eof);
		printf("\n");
		printf("Cmd: ");
		print_args(cmds[i].args);
		printf("\n--------------CMD: %d END--------------\n", i + 1);
		printf("\nvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv\n");
	}
}


void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	size_t	copysize;
	void	*new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (!ptr)
		return (new_ptr);
	if (old_size < new_size)
		copysize = old_size;
	else
		copysize = new_size;
	ft_memcpy(new_ptr, ptr, copysize);
	free(ptr);
	return (new_ptr);
}

t_list_cmds	*cmd_parse(char *line, char *delim, int *count)
{
	t_list_cmds	*cmds;
	t_list_cmds	cmd;
	int			next_size;
	int			cmd_count;
	char			*cmd_str;

	cmds = NULL;
	cmd_count = 0;
	cmd_str = next_token(line, delim);
	while (cmd_str)
	{
//		printf("\n%s\n", cmd_str);
		cmd.heredoc_fd = -1;
		cmd.bltin = -1;
		cmd.file_toappend = NULL;
		cmd.file_toread = NULL;
		cmd.all_eof = NULL;
		cmd.eof = NULL;
		cmd.args = ft_split(cmd_str, ' '); //split and unpack
		next_size = (cmd_count + 1) * sizeof(t_list_cmds);
		cmds = ft_realloc(cmds, (cmd_count) * sizeof(t_list_cmds), next_size);
		cmds[cmd_count++] = cmd;
		free(cmd_str);
		cmd_str = next_token(NULL, delim);
	}
	*count = cmd_count;
	return (cmds);
}

int	prepare_cmds(t_list_cmds **cmds, char *line, char **envp, int **cnt_lst)
{
	int	cmd_count;
	t_list_cmds	*temp;

	cmd_count = 0;
	temp = cmd_parse(line, "|", &cmd_count);
	parse_path(temp, envp, cmd_count);
	if (rephrase_cmd(temp, cmd_count, envp, *(cnt_lst[1])) == 2)
		return (-1);
	*(cnt_lst[0]) = cmd_count;
	*cmds = temp;
	info_printpipetokens(temp, cmd_count);
	return (1);
}
