/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_and_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiascha <phiascha@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:40:38 by phiascha          #+#    #+#             */
/*   Updated: 2025/06/14 14:25:25 by phiascha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	check_pipe2(t_token *tokens)
{
	if (tokens->type == TK_PIPE)
	{
		print_error("Error: unclosed pipe\n");
		return (false);
	}
	else if (tokens->type > 1)
	{
		print_error("syntax error near unexpected token 'newline'\n");
		return (false);
	}
	return (true);
}

bool	check_pipe(t_token *tokens)
{
	if (tokens->type == TK_PIPE)
	{
		print_error("syntax error near unexpected token '|'\n");
		return (false);
	}
	while (tokens)
	{
		if (tokens->type == TK_PIPE && tokens->next
			&& tokens->next->type == TK_PIPE)
		{
			print_error("syntax error near unexpected token '|'\n");
			return (false);
		}
		if (tokens->type > 1 && tokens->next && tokens->next->type != TK_WORD)
		{
			print_error_tok(tokens->next->type);
			return (false);
		}
		if (!tokens->next)
			break ;
		tokens = tokens->next;
	}
	return (check_pipe2(tokens));
}

static bool	quote_return(int quote, char *line, t_data *data)
{
	if (quote == -1)
		return (false);
	free(line);
	data->exit_code = 2;
	print_error("open quote\n");
	return (true);
}

bool	open_quote(char *line, t_data *data)
{
	int	quote;
	int	i;

	quote = -1;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			quote = i;
			i++;
			while (line[i] && line[i] != line[quote])
				i++;
			if (line[i] == line[quote])
			{
				i++;
				quote = -1;
			}
		}
		else
			i++;
	}
	return (quote_return(quote, line, data));
}
