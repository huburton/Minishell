/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:54:03 by huburton          #+#    #+#             */
/*   Updated: 2025/06/13 18:54:04 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	check_n(char *str)
{
	size_t	i;

	if (str[0] == '-')
	{
		i = 1;
		while (str[i] && str[i] == 'n')
			i++;
		if (i >= 2 && i == ft_strlen(str))
			return (true);
	}
	return (false);
}

int	ft_echo(char **str)
{
	int		i;
	bool	new_line;

	new_line = true;
	i = 1;
	while (str[i])
	{
		if (check_n(str[i]))
		{
			new_line = false;
			i++;
		}
		else
			break ;
	}
	while (str[i])
	{
		write(1, str[i], ft_strlen(str[i]));
		if (str[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (new_line == true)
		write(1, "\n", 1);
	return (0);
}
