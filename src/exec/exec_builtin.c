/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiascha <phiascha@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:41:15 by phiascha          #+#    #+#             */
/*   Updated: 2025/06/16 22:25:40 by phiascha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "exit")
		|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env"))
		return (true);
	return (false);
}

int	exec_builtin(t_cmd *cmd, t_data *data)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (!ft_strcmp(cmd->args[0], "cd"))
		return (ft_cd(&data->env, cmd->args));
	if (!ft_strcmp(cmd->args[0], "echo"))
		return (ft_echo(cmd->args));
	if (!ft_strcmp(cmd->args[0], "pwd"))
		return (ft_pwd());
	if (!ft_strcmp(cmd->args[0], "env"))
		return (ft_env(data->env));
	if (!ft_strcmp(cmd->args[0], "export"))
		return (ft_export(cmd->args, &data->env));
	if (!ft_strcmp(cmd->args[0], "unset"))
		return (ft_unset(cmd->args, &data->env));
	return (1);
}

int	exec_builtin_redir(t_cmd *cmd, t_data *data)
{
	int	ret;
	int	original_stdout;

	if (cmd->fd_in == -1)
		return (1);
	if (!ft_strcmp(cmd->args[0], "exit"))
		return (ft_exit(cmd->args, *data));
	if (cmd->fd_out != -2)
	{
		original_stdout = dup(STDOUT_FILENO);
		dup2(cmd->fd_out, STDOUT_FILENO);
	}
	ret = exec_builtin(cmd, data);
	if (cmd->fd_out != -2)
	{
		dup2(original_stdout, STDOUT_FILENO);
		close(original_stdout);
	}
	return (ret);
}
