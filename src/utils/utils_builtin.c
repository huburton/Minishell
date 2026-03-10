/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiascha <phiascha@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:40:12 by phiascha          #+#    #+#             */
/*   Updated: 2025/06/16 22:14:22 by phiascha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	is_valid(char *str)
{
	int	i;

	if (!str[0] || (str[0] != '_' && !ft_isalpha(str[0])))
		return (false);
	i = 0;
	while (str[i] && str[i] != '=' && !(str[i] == '+' && str[i + 1] == '='))
	{
		if (str[i] != '_' && !ft_isalnum(str[i]))
			return (false);
		i++;
	}
	return (true);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	ft_sort_array(char **env)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				temp = env[i];
				env[i] = env[j];
				env[j] = temp;
			}
			j++;
		}
		i++;
	}
}

char	**make_env(char **env)
{
	int		count;
	char	**new_env;

	if (!env)
		return (NULL);
	count = 0;
	while (env[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (NULL);
	count = 0;
	while (env[count])
	{
		new_env[count] = ft_strdup(env[count]);
		if (!new_env[count])
			return (free_env(new_env));
		count++;
	}
	new_env[count] = NULL;
	return (new_env);
}
