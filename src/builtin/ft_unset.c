/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiascha <phiascha@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:54:21 by huburton          #+#    #+#             */
/*   Updated: 2025/06/16 22:05:50 by phiascha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	find_pos(char *str, char **env)
{
	int	len;
	int	pos;

	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	pos = 0;
	while (env[pos])
	{
		if (!ft_strncmp(env[pos], str, len))
			return (pos);
		pos++;
	}
	return (-1);
}

static char	**ft_remove(char **env, int pos)
{
	int		count;
	char	**new_env;

	count = 0;
	while (env[count])
		count++;
	new_env = malloc(sizeof(char *) * count);
	if (!new_env)
		return (NULL);
	count = 0;
	while ((count < pos && env[count]) || env[count + 1])
	{
		if (count < pos)
			new_env[count] = ft_strdup(env[count]);
		else
			new_env[count] = ft_strdup(env[count + 1]);
		if (!new_env[count])
			return (free_env(new_env));
		count++;
	}
	new_env[count] = NULL;
	return (new_env);
}

static char	**make_new_env(char **env, int pos)
{
	char	**new_env;

	new_env = ft_remove(env, pos);
	free_env(env);
	if (!new_env)
	{
		print_error("Malloc error\n");
		return (NULL);
	}
	return (new_env);
}

int	ft_unset(char **str, char ***env)
{
	int		error_num;
	int		i;
	int		pos;

	if (!(*env) || !(*env)[0])
		return (0);
	error_num = 0;
	i = 1;
	while (str[i])
	{
		if (!is_valid(str[i]))
			error_num = 1;
		else
		{
			pos = find_pos(str[i], *env);
			if (pos > -1)
			{
				*env = make_new_env(*env, pos);
				if (!(*env))
					return (1);
			}
		}
		i++;
	}
	return (error_num);
}
