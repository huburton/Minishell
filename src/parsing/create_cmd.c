/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiascha <phiascha@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:40:56 by phiascha          #+#    #+#             */
/*   Updated: 2025/06/15 05:40:12 by phiascha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_args(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens && tokens->type != TK_PIPE)
	{
		if (tokens->str)
			count++;
		else if (tokens->type != TK_WORD && tokens->next)
			tokens = tokens->next;
		tokens = tokens->next;
	}
	return (count);
}

t_cmd	*new_cmd(t_token *tokens)
{
	t_cmd	*cmd;
	int		arg_count;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
	{
		print_error("Malloc error\n");
		return (NULL);
	}
	cmd->fd_in = -2;
	cmd->fd_out = -2;
	cmd->next = NULL;
	arg_count = count_args(tokens);
	cmd->args = ft_calloc(arg_count + 1, sizeof(char *));
	if (!cmd->args)
	{
		print_error("Malloc error\n");
		free(cmd);
		return (NULL);
	}
	return (cmd);
}

bool	open_file(t_token *tokens, t_cmd *cmd, t_data data)
{
	int	fd;

	if (!check_file(tokens, cmd, data))
		return (false);
	if (tokens->type == TK_REDIR_IN)
		fd = open(tokens->next->str, O_RDONLY);
	else if (tokens->type == TK_REDIR_OUT)
		fd = open(tokens->next->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (tokens->type == TK_REDIR_APPEND)
		fd = open(tokens->next->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd = heredoc(data, tokens->next->str);
	if (fd < 0)
		error_close_fd(tokens, cmd);
	else if (tokens->type == TK_REDIR_IN || tokens->type == TK_HEREDOC)
		cmd->fd_in = fd;
	else
		cmd->fd_out = fd;
	return (true);
}

t_token	*fill_cmd(t_token *tokens, t_cmd *cmd, t_data data, int *index)
{
	if (tokens->type == TK_WORD)
	{
		if (!tokens->str)
			return (tokens);
		cmd->args[*index] = ft_strdup(tokens->str);
		if (!cmd->args[*index])
		{
			print_error("Malloc error\n");
			return (NULL);
		}
		(*index)++;
	}
	else if (tokens->next && tokens->next->type == TK_WORD)
	{
		if (tokens->next->str && (cmd->fd_in != -1
				|| tokens->type == TK_HEREDOC))
		{
			if (!open_file(tokens, cmd, data))
				return (NULL);
		}
		tokens = tokens->next;
	}
	return (tokens);
}

t_cmd	*build_cmds(t_token *tokens, t_data data)
{
	t_cmd	*cmd_list;
	t_cmd	*current_cmd;
	int		index;

	cmd_list = NULL;
	while (tokens)
	{
		current_cmd = new_cmd(tokens);
		if (!current_cmd)
			return (free_cmds(cmd_list));
		index = 0;
		while (tokens && tokens->type != TK_PIPE)
		{
			tokens = fill_cmd(tokens, current_cmd, data, &index);
			if (!tokens)
				return (append_free(cmd_list, current_cmd));
			tokens = tokens->next;
		}
		if (tokens)
			tokens = tokens->next;
		append_cmd(&cmd_list, current_cmd);
	}
	return (cmd_list);
}
