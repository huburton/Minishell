/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 00:00:00 by phiascha          #+#    #+#             */
/*   Updated: 2025/06/17 14:57:44 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	has_equal_sign(char *str)
{
	return (ft_strchr(str, '=') != NULL);
}

bool	is_append_mode(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (true);
		i++;
	}
	return (false);
}

static char	*get_var_name(char *str)
{
	char	*plus_pos;

	plus_pos = ft_strchr(str, '+');
	if (!plus_pos)
		return (NULL);
	return (ft_substr(str, 0, plus_pos - str));
}

static char	*get_old_value(char *existing)
{
	char	*equal_pos;

	equal_pos = ft_strchr(existing, '=');
	if (!equal_pos)
		return (ft_strdup(""));
	return (ft_strdup(equal_pos + 1));
}

char	*handle_append_mode(char *str, char *existing)
{
	char	*var_name;
	char	*old_val;
	char	*new_val;
	char	*temp;
	char	*result;

	var_name = get_var_name(str);
	if (!var_name)
		return (NULL);
	old_val = get_old_value(existing);
	if (!old_val)
		return (free(var_name), NULL);
	new_val = ft_strchr(str, '=') + 1;
	temp = ft_strjoin(old_val, new_val);
	free(old_val);
	if (!temp)
		return (free(var_name), NULL);
	result = ft_strjoin(var_name, "=");
	free(var_name);
	if (!result)
		return (free(temp), NULL);
	var_name = ft_strjoin(result, temp);
	return (free(result), free(temp), var_name);
}
