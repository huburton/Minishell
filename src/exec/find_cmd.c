/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiascha <phiascha@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:41:03 by phiascha          #+#    #+#             */
/*   Updated: 2025/06/14 13:39:55 by phiascha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*join_path(const char *dir, const char *cmd)
{
	size_t	len1;
	size_t	len2;
	char	*full;

	len1 = ft_strlen(dir);
	len2 = ft_strlen(cmd);
	full = malloc(len1 + len2 + 2);
	if (!full)
	{
		print_error("Malloc error\n");
		return (NULL);
	}
	ft_strlcpy(full, dir, len1 + 1);
	ft_strlcat(full, "/", len1 + 2);
	ft_strlcat(full, cmd, len1 + len2 + 2);
	return (full);
}

static char	*next_path(char **rest)
{
	char	*start;
	int		i;

	if (!*rest || **rest == '\0')
		return (NULL);
	start = *rest;
	i = 0;
	while (start[i] && start[i] != ':')
		i++;
	if (start[i] == ':')
	{
		start[i] = '\0';
		*rest = &start[i + 1];
	}
	else
		*rest = NULL;
	return (start);
}

static char	*find_full_cmd(char *cmd, t_data data)
{
	char	*full;

	if (access(cmd, X_OK) == 0)
	{
		full = ft_strdup(cmd);
		if (!full)
		{
			print_error("Malloc error\n");
			free_all(data, 1);
		}
		check_reg(full, cmd, data);
		return (full);
	}
	if (access(cmd, F_OK) == 0)
	{
		print_error(cmd);
		print_error(": Permission denied\n");
		free_all(data, 126);
	}
	print_error(cmd);
	print_error(": No such file or directory\n");
	free_all(data, 127);
	return (NULL);
}

static char	*find_joined_cmd(char *paths, char *cmd, t_data data)
{
	char	*cursor;
	char	*dir;
	char	*full;

	cursor = paths;
	dir = next_path(&cursor);
	while (dir)
	{
		full = join_path(dir, cmd);
		if (!full)
		{
			free(paths);
			free_all(data, 1);
			return (NULL);
		}
		if (access(full, X_OK) == 0)
			return (found_cmd(paths, cmd, full, data));
		free(full);
		dir = next_path(&cursor);
	}
	print_error_cmd(cmd);
	free(paths);
	free_all(data, 127);
	return (NULL);
}

char	*resolve_path(char *cmd, t_data data)
{
	char	*path_env;
	char	*paths;

	if (ft_strchr(cmd, '/'))
		return (find_full_cmd(cmd, data));
	path_env = get_env_value("PATH", data.env);
	if (!path_env)
	{
		print_error(cmd);
		print_error(": No such file or directory\n");
		free_all(data, 127);
	}
	paths = ft_strdup(path_env);
	if (!paths)
	{
		print_error("Malloc error\n");
		free_all(data, 1);
	}
	return (find_joined_cmd(paths, cmd, data));
}
