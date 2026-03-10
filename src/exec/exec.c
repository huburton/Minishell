/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiascha <phiascha@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:41:12 by phiascha          #+#    #+#             */
/*   Updated: 2025/06/17 15:35:13 by phiascha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	redirect(t_cmd *cmd, int *pipe_fd, int prev_fd)
{
	if (cmd->fd_in >= 0)
		dup2(cmd->fd_in, STDIN_FILENO);
	else if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->fd_out >= 0)
		dup2(cmd->fd_out, STDOUT_FILENO);
	else if (cmd->fd_out == -2 && cmd->next)
		dup2(pipe_fd[1], STDOUT_FILENO);
	if (cmd->next)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
}

static void	child_process(t_cmd *cmd, t_data *data, int *pipe_fd, int prev_fd)
{
	char	*resolved_path;

	redirect(cmd, pipe_fd, prev_fd);
	if (cmd->fd_in == -1)
		free_all(*data, 1);
	else if (!cmd->args[0])
		free_all(*data, 0);
	else if (!ft_strcmp(cmd->args[0], "exit"))
		ft_exit_pipe(cmd->args, *data);
	else if (is_builtin(cmd->args[0]))
		free_all(*data, exec_builtin(cmd, data));
	else
	{
		resolved_path = resolve_path(cmd->args[0], *data);
		execve(resolved_path, cmd->args, data->env);
		perror("execve");
		free(resolved_path);
		free_all(*data, 1);
	}
}

static int	wait_proc(pid_t last_pid)
{
	int	status;
	int	wpid;
	int	last_status;

	last_status = 0;
	status = 0;
	wpid = wait(&status);
	while (wpid > 0)
	{
		if (wpid == last_pid && WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		wpid = wait(&status);
	}
	return (last_status);
}

int	exec_cmd(t_cmd *cmd, t_data *data)
{
	int		pipe_fd[2];
	int		prev_fd;
	pid_t	pid;
	pid_t	last_pid;

	prev_fd = -1;
	last_pid = -1;
	if (cmd->next == NULL && is_builtin(cmd->args[0]))
		return (exec_builtin_redir(cmd, data));
	while (cmd)
	{
		if (cmd->next && pipe(pipe_fd) == -1)
			return (pipe_err(prev_fd));
		pid = fork();
		if (pid == -1)
			return (fork_err(cmd, pipe_fd, prev_fd));
		if (pid == 0)
			child_process(cmd, data, pipe_fd, prev_fd);
		parent_process(cmd, pipe_fd, &prev_fd);
		last_pid = pid;
		cmd = cmd->next;
	}
	return (wait_proc(last_pid));
}
