/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 16:13:42 by ksan              #+#    #+#             */
/*   Updated: 2025/12/28 13:34:03 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_count(char *str)
{
	int		count;
	int		sp_case;
	char	*token;

	count = 0;
	sp_case = 0;
	token = next_token(str, "<<");
	if (ft_strlen(token) == 0)
		sp_case = 1;
	while (token)
	{
		count++;
		free(token);
		token = next_token(NULL, "<<");
	}
	if (sp_case)
		count = (count + (count - 1)) - 1;
	else
		count = count + (count - 1);
	if (str[ft_strlen(str) - 1] == '>' && (str[ft_strlen(str) - 2] == '>'))
		count++;
	return (count);
}

static int	get_total_count(char **cmd, int old_count)
{
	int	new_count;
	int	i;

	new_count = 0;
	i = -1;
	while (++i < old_count)
	{
		if (ft_strnstr(cmd[i], "<<", ft_strlen(cmd[i]))
			&& ft_strlen(cmd[i]) > 2)
			new_count += get_count(cmd[i]);
		else
			new_count++;
	}
	return (new_count);
}

static void	append_token(char **new_cmd, int *i, char *str)
{
	char	*token;

	token = next_token(str, "<<");
	while (token)
	{
		if (ft_strlen(token))
			new_cmd[(*i)++] = token;
		else
			free(token);
		token = next_token(NULL, "<<");
		if (token)
			new_cmd[(*i)++] = ft_strdup("<<");
	}
	if (str[ft_strlen(str) - 1] == '>' && (str[ft_strlen(str) - 2] == '>'))
		new_cmd[(*i)++] = ft_strdup("<<");
}

static char	**expand_nested(char **cmd, int *count)
{
	int		old_count;
	int		new_count;
	int		i;
	int		new_i;
	char	**expanded;

	old_count = 0;
	while (cmd[old_count])
		old_count++;
	new_count = get_total_count(cmd, old_count);
	expanded = malloc(sizeof(char *) * (new_count + 1));
	i = -1;
	new_i = 0;
	while (++i < old_count)
	{
		if (ft_strnstr(cmd[i], "<<", ft_strlen(cmd[i]))
			&& ft_strlen(cmd[i]) > 2)
			append_token(expanded, &new_i, cmd[i]);
		else
			expanded[new_i++] = ft_strdup(cmd[i]);
	}
	expanded[new_count] = NULL;
	*count = new_count;
	return (expanded);
}

int	prepare_heredoc(t_list_cmds *full_cmd)
{
	int		final_count;
	int		redir_append;
	int		i;
	char	**cmd;
	char	**temp;

	cmd = full_cmd->args;
	redir_append = 0;
	final_count = 0;
	i = -1;
	while (cmd[++i])
	{
		if (ft_strnstr(cmd[i], "<<", ft_strlen(cmd[i])))
		{
			redir_append = 1;
			break ;
		}
	}
	if (redir_append)
	{
		temp = expand_nested(cmd, &final_count);
		free_arg(cmd);
		full_cmd->args = temp;
	}
	return (final_count);
}
