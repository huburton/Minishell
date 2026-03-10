/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiascha <phiascha@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:54:12 by huburton          #+#    #+#             */
/*   Updated: 2025/06/16 22:19:50 by phiascha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	print_export(char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		printf("declare -x ");
		j = 0;
		while (env[i][j] && env[i][j] != '=')
		{
			printf("%c", env[i][j]);
			j++;
		}
		if (env[i][j] && env[i][j] == '=')
			printf("=\"%s\"\n", &env[i][j + 1]);
		else
			printf("\n");
		i++;
	}
}

static bool	sort_and_print(char **env)
{
	char	**sorted_env;

	sorted_env = make_env(env);
	if (!sorted_env)
	{
		print_error("Malloc error\n");
		return (false);
	}
	ft_sort_array(sorted_env);
	print_export(sorted_env);
	free_env(sorted_env);
	return (true);
}

int	ft_export(char **str, char ***env)
{
	int	error_num;
	int	i;

	error_num = 0;
	i = 1;
	if (!str || !str[i])
	{
		if (*env && !sort_and_print(*env))
			return (1);
		return (0);
	}
	while (str[i])
	{
		if (!is_valid(str[i]))
		{
			error_num = 1;
			print_error("export: '");
			print_error(str[i]);
			print_error("': not a valid identifier\n");
		}
		else if (!ft_export_str(str[i], env))
			return (1);
		i++;
	}
	return (error_num);
}
