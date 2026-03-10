/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:53:58 by huburton          #+#    #+#             */
/*   Updated: 2025/06/14 17:21:07 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	update_oldpwd(char ***env, char *cwd)
{
	char	*oldpwd;

	oldpwd = ft_strjoin("OLDPWD=", cwd);
	if (!oldpwd)
	{
		print_error("Malloc error\n");
		return (false);
	}
	ft_export_str(oldpwd, env);
	free(oldpwd);
	return (true);
}

static int	update_env(char ***env, char *dir, char *cwd)
{
	char	*pwd;

	if (!update_oldpwd(env, cwd))
		return (1);
	if (!getcwd(cwd, PATH_MAX))
	{
		perror(dir);
		return (1);
	}
	pwd = ft_strjoin("PWD=", cwd);
	if (!pwd)
	{
		print_error("Malloc error\n");
		return (1);
	}
	ft_export_str(pwd, env);
	free(pwd);
	return (0);
}

static char	*get_target_dir(char **args, char **env)
{
	char	*target_dir;

	if (!args[1] || !ft_strcmp(args[1], "~"))
	{
		target_dir = get_env_value("HOME", env);
		if (!target_dir)
		{
			print_error("cd: HOME not set\n");
			return (NULL);
		}
	}
	else if (!args[1] || !ft_strcmp(args[1], "-"))
	{
		target_dir = get_env_value("OLDPWD", env);
		if (!target_dir)
		{
			print_error("cd: OLDPWD not set\n");
			return (NULL);
		}
	}
	else
		target_dir = args[1];
	return (target_dir);
}

static int	handle_cd_init(char ***env, char **args, char *cwd)
{
	char	*home_dir;

	if (args[1] && args[2])
	{
		print_error("cd: too many arguments\n");
		return (1);
	}
	if (!getcwd(cwd, PATH_MAX))
	{
		home_dir = get_env_value("HOME", *env);
		if (home_dir)
			return (chdir(home_dir));
		else
		{
			perror("getcwd");
			return (1);
		}
	}
	return (0);
}

int	ft_cd(char ***env, char **args)
{
	int		ret;
	char	cwd[PATH_MAX];
	char	*target_dir;

	ret = handle_cd_init(env, args, cwd);
	if (ret != 0)
		return (ret);
	target_dir = get_target_dir(args, *env);
	if (!target_dir)
		return (1);
	ret = chdir(target_dir);
	if (ret == 0)
		return (update_env(env, target_dir, cwd));
	else
	{
		perror(target_dir);
		return (1);
	}
}
