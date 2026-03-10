/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:54:15 by huburton          #+#    #+#             */
/*   Updated: 2025/06/17 15:04:00 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	**ft_append(char *str, char **env)
{
	int		count;
	char	**new_env;

	count = 0;
	while (env && env[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (NULL);
	count = 0;
	while (env && env[count])
	{
		new_env[count] = ft_strdup(env[count]);
		if (!new_env)
			return (free_env(new_env));
		count++;
	}
	new_env[count] = ft_strdup(str);
	if (!new_env)
		return (free_env(new_env));
	new_env[count + 1] = NULL;
	return (new_env);
}

static int	find_pos(char *str, char **env)
{
	int	len;
	int	pos;

	if (!env)
		return (-1);
	len = 0;
	while (str[len] && str[len] != '=' && str[len] != '+')
		len++;
	pos = 0;
	while (env[pos])
	{
		if (!ft_strncmp(env[pos], str, len) && (env[pos][len] == '\0'
			|| env[pos][len] == '='))
			return (pos);
		pos++;
	}
	return (-1);
}

static char	**make_new_env(char *temp, char **env)
{
	char	**new_env;

	new_env = ft_append(temp, env);
	if (env)
		free_env(env);
	if (!new_env)
	{
		print_error("Malloc error\n");
		return (NULL);
	}
	return (new_env);
}

static bool	handle_existing_var(char *str, char ***env, int pos)
{
	char	*new_var;

	if (!has_equal_sign(str))
		return (true);
	if (is_append_mode(str))
		new_var = handle_append_mode(str, (*env)[pos]);
	else
		new_var = ft_strdup(str);
	if (!new_var)
	{
		print_error("Malloc error\n");
		return (false);
	}
	free((*env)[pos]);
	(*env)[pos] = new_var;
	return (true);
}

bool	ft_export_str(char *str, char ***env)
{
	int		pos;

	pos = find_pos(str, *env);
	if (pos >= 0)
		return (handle_existing_var(str, env, pos));
	else if (pos == -1)
	{
		*env = make_new_env(str, *env);
		if (!(*env))
			return (false);
	}
	return (true);
}
