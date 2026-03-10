/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiascha <phiascha@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:40:24 by phiascha          #+#    #+#             */
/*   Updated: 2025/06/14 11:38:25 by phiascha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_env_value(char *name, char **env)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(name);
	while (env[i])
	{
		if (!ft_strncmp(env[i], name, len) && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

bool	is_space(char c)
{
	if (c && ((c >= 9 && c <= 13) || c == 32))
		return (true);
	return (false);
}

void	check_reg(char *path, char *cmd, t_data data)
{
	struct stat	stat_struc;

	stat(path, &stat_struc);
	if (!S_ISREG(stat_struc.st_mode))
	{
		free(path);
		print_error(cmd);
		print_error(" : Is a directory\n");
		free_all(data, 126);
	}
}

char	*found_cmd(char *paths, char *cmd, char *full, t_data data)
{
	free(paths);
	check_reg(full, cmd, data);
	return (full);
}

bool	empty_line(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	if (i == ft_strlen(line))
	{
		free(line);
		return (true);
	}
	return (false);
}
