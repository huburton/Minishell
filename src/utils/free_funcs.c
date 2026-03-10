/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiascha <phiascha@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:40:30 by phiascha          #+#    #+#             */
/*   Updated: 2025/06/16 18:08:07 by phiascha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
	return (NULL);
}

t_token	*free_tokens(t_token *head)
{
	t_token	*temp;

	while (head)
	{
		temp = head->next;
		if (head->str)
			free(head->str);
		free(head);
		head = temp;
	}
	return (NULL);
}

t_cmd	*free_cmds(t_cmd *head)
{
	t_cmd	*temp;
	int		i;

	while (head)
	{
		temp = head->next;
		close_fd(head);
		if (head->args)
		{
			i = 0;
			while (head->args[i])
			{
				free(head->args[i]);
				i++;
			}
			free(head->args);
		}
		free(head);
		head = temp;
	}
	return (NULL);
}

void	free_all(t_data data, int exit_code)
{
	rl_clear_history();
	free_cmds(data.cmds);
	free_env(data.env);
	exit(exit_code);
}

t_cmd	*append_free(t_cmd *cmd_list, t_cmd *current_cmd)
{
	append_cmd(&cmd_list, current_cmd);
	return (free_cmds(cmd_list));
}
