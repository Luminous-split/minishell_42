/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:42:16 by soemin            #+#    #+#             */
/*   Updated: 2025/09/22 20:07:04 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*tilde_and_dash(char **args, int ac, char **env)
{
	char	*target;

	if (ac == 1 || (ac == 2 && ft_strncmp(args[1], "~", 2) == 0))
	{
		target = getenv("HOME");
		if (!target)
			printf("cd: HOME not set\n");
		return (target);
	}
	if (ac == 2 && ft_strncmp(args[1], "-", 2) == 0)
	{
		target = get_env_var(env, "OLDPWD");
		if (!target)
			printf("cd: OLDPWD not set\n");
		else
			printf("%s\n", target);
		return (target);
	}
	return (NULL);
}

static char	*expand_tilde(const char *target)
{
	char		*home;
	static char	buffer[PATH_MAX];

	if (target[0] == '~')
	{
		home = getenv("HOME");
		if (!home)
		{
			printf("cd: HOME not set\n");
			return (NULL);
		}
		ft_strlcpy(buffer, home, PATH_MAX);
		if (target[1] == '/' || target[1] == '\0')
			ft_strlcat(buffer, target + 1, PATH_MAX);
		return (buffer);
	}
	return ((char *)target);
}

static char	*get_cd_target(char **args, int ac, char **env)
{
	char	*target;

	target = tilde_and_dash(args, ac, env);
	if (target)
		return (target);
	if (ac >= 2)
		return (expand_tilde(args[1]));
	return (NULL);
}

static int	cd_and_set_env(const char *target, char **env, const char *prev_dir)
{
	char	cwd[PATH_MAX];

	if (chdir(target) != 0)
	{
		printf("cd: %s: %s\n", target, strerror(errno));
		return (0);
	}
	if (getcwd(cwd, sizeof(cwd)))
	{
		set_env_var(env, "OLDPWD", prev_dir);
		set_env_var(env, "PWD", cwd);
	}
	else
	{
		perror("cd: getcwd");
		return (0);
	}
	return (1);
}

int	ft_cd(char **args, char **envp)
{
	int		ac;
	char	prev_dir[PATH_MAX];
	char	*target;

	ac = count_args(args);
	if (ac > 2)
	{
		printf("cd: too many arguments\n");
		return (0);
	}
	if (!getcwd(prev_dir, sizeof(prev_dir)))
	{
		perror("cd: getcwd");
		return (0);
	}
	target = get_cd_target(args, ac, env);
	if (!target)
		return (0);
	return (cd_and_set_env(target, env, prev_dir));
}
