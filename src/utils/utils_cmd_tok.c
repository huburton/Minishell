/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd_tok.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiascha <phiascha@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:40:09 by phiascha          #+#    #+#             */
/*   Updated: 2025/06/15 06:19:36 by phiascha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	append_token(t_token **head, t_token *new)
{
	t_token	*temp;

	if (!*head)
		*head = new;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

void	append_cmd(t_cmd **head, t_cmd *new)
{
	t_cmd	*temp;

	if (!*head)
		*head = new;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

bool	ambiguous_redir(char *str, t_cmd *cmd)
{
	close_fd(cmd);
	cmd->fd_in = -1;
	cmd->fd_out = -1;
	print_error(str);
	print_error(": ambiguous redirect\n");
	return (false);
}

bool	check_file(t_token *tokens, t_cmd *cmd, t_data data)
{
	char	*temp;

	if (tokens->type != TK_HEREDOC && tokens->next->str[0] == '$'
		&& !get_env_value(tokens->next->str + 1, data.env))
		return (ambiguous_redir(tokens->next->str, cmd));
	else if (tokens->type != TK_HEREDOC)
	{
		temp = expand_variables(tokens->next->str, data);
		if (!temp)
			return (false);
		free(tokens->next->str);
		tokens->next->str = temp;
	}
	if ((tokens->type == TK_REDIR_IN || tokens->type == TK_HEREDOC)
		&& cmd->fd_in >= 0)
		close(cmd->fd_in);
	else if ((tokens->type == TK_REDIR_OUT || tokens->type == TK_REDIR_APPEND)
		&& cmd->fd_out >= 0)
		close(cmd->fd_out);
	return (true);
}

void	error_close_fd(t_token *tokens, t_cmd *cmd)
{
	if (tokens->type != TK_HEREDOC)
		perror(tokens->next->str);
	close_fd(cmd);
	cmd->fd_in = -1;
	cmd->fd_out = -1;
}
