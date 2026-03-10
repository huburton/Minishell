/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiascha <phiascha@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:41:07 by phiascha          #+#    #+#             */
/*   Updated: 2025/06/17 15:15:35 by phiascha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	close_fd(t_cmd *cmd)
{
	if (cmd->fd_in >= 0)
		close(cmd->fd_in);
	if (cmd->fd_out >= 0)
		close(cmd->fd_out);
}

void	parent_process(t_cmd *cmd, int *pipe_fd, int *prev_fd)
{
	if (*prev_fd != -1)
	{
		close(*prev_fd);
		*prev_fd = -1;
	}
	if (cmd->next)
	{
		close(pipe_fd[1]);
		if (cmd->next->fd_in == -2)
			*prev_fd = pipe_fd[0];
		else
			close(pipe_fd[0]);
	}
}

int	pipe_err(int prev_fd)
{
	perror("pipe");
	if (prev_fd != -1)
		close(prev_fd);
	return (1);
}

int	fork_err(t_cmd *cmd, int *pipe_fd, int prev_fd)
{
	perror("fork");
	if (prev_fd != -1)
		close(prev_fd);
	if (cmd->next)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	return (1);
}
