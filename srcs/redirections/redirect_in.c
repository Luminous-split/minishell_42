/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 16:13:42 by ksan              #+#    #+#             */
/*   Updated: 2025/12/28 13:35:34 by ksan             ###   ########.sg       */
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
	token = next_token(str, "<");
	if (ft_strlen(token) == 0)
		sp_case = 1;
	while (token)
	{
		count++;
		free(token);
		token = next_token(NULL, "<");
	}
	if (sp_case)
		count = (count + (count - 1)) - 1;
	else
		count = count + (count - 1);
	if (str[ft_strlen(str) - 1] == '<')
		count++;
	return (count);
}

static int	get_total_count(char **cmd, int old_count)
{
	int		new_count;
	int		i;
	char	*check_ptr;

	new_count = 0;
	i = -1;
	while (++i < old_count)
	{
		check_ptr = ft_strnstr(cmd[i], "<", ft_strlen(cmd[i]));
		if (check_ptr && *(check_ptr + 1) != '<' && ft_strlen(cmd[i]) > 1)
			new_count += get_count(cmd[i]);
		else
			new_count++;
	}
	return (new_count);
}

static void	append_token(char **new_cmd, int *i, char *str)
{
	char	*token;

	token = next_token(str, "<");
	while (token)
	{
		if (ft_strlen(token))
			new_cmd[(*i)++] = token;
		token = next_token(NULL, "<");
		if (token)
			new_cmd[(*i)++] = ft_strdup("<");
	}
	if (str[ft_strlen(str) - 1] == '<')
		new_cmd[(*i)++] = ft_strdup("<");
}

static char	**expand_nested(char **cmd, int old_count)
{
	int		new_count;
	int		i;
	int		new_i;
	char	**expanded;
	char	*check_ptr;

	new_count = get_total_count(cmd, old_count);
	expanded = malloc(sizeof(char *) * (new_count + 1));
	i = -1;
	new_i = 0;
	while (++i < old_count)
	{
		check_ptr = ft_strnstr(cmd[i], "<", ft_strlen(cmd[i]));
		if (check_ptr && *(check_ptr + 1) != '<' && ft_strlen(cmd[i]) > 1)
			append_token(expanded, &new_i, cmd[i]);
		else
			expanded[new_i++] = ft_strdup(cmd[i]);
	}
	expanded[new_count] = NULL;
	return (expanded);
}

void	prepare_inredir(t_list_cmds *full_cmd)
{
	int		old_count;
	int		i;
	int		redir;
	char	**temp;
	char	*check_ptr;

	old_count = 0;
	redir = 0;
	i = -1;
	while (full_cmd->args[++i])
	{
		check_ptr = ft_strnstr(full_cmd->args[i], "<",
				ft_strlen(full_cmd->args[i]));
		if (check_ptr && *(check_ptr + 1) != '<')
			redir = 1;
		old_count++;
	}
	if (redir)
	{
		temp = expand_nested(full_cmd->args, old_count);
		free(full_cmd->args);
		full_cmd->args = temp;
	}
	return ;
}
