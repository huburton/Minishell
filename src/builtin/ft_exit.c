/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiascha <phiascha@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:54:07 by huburton          #+#    #+#             */
/*   Updated: 2025/06/19 00:51:43 by phiascha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_atoi_exit2(char *str, bool *error, int i, int sign)
{
	unsigned long long	result;
	int					j;

	j = i;
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	if (i - j > 19 || (result > LLONG_MAX && sign == 1)
		|| (result - 1 > LLONG_MAX && sign == -1))
		*error = true;
	while (is_space(str[i]))
		i++;
	if (str[i])
		*error = true;
	return ((int)((result * sign) % 256));
}

static int	ft_atoi_exit(char *str, bool *error)
{
	int	i;
	int	sign;

	sign = 1;
	i = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] == '0')
		i++;
	return (ft_atoi_exit2(str, error, i, sign));
}

static int	find_exit_code(char *str)
{
	int		ret;
	bool	error;

	error = false;
	ret = ft_atoi_exit(str, &error);
	if (error)
	{
		print_error("exit: ");
		print_error(str);
		print_error(": numeric argument required\n");
		return (2);
	}
	return (ret);
}

int	ft_exit(char **str, t_data data)
{
	int	exit_code;

	printf("exit\n");
	if (str[1] && str[2])
	{
		print_error("exit: too many arguments\n");
		return (1);
	}
	if (!str[1])
		exit_code = data.exit_code;
	else
		exit_code = find_exit_code(str[1]);
	free_all(data, exit_code);
	return (0);
}

void	ft_exit_pipe(char **str, t_data data)
{
	int	exit_code;

	if (str[1] && str[2])
	{
		print_error("exit: too many arguments\n");
		exit(1);
	}
	if (!str[1])
		exit_code = data.exit_code;
	else
		exit_code = find_exit_code(str[1]);
	free_all(data, exit_code);
}
