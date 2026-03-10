/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiascha <phiascha@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:40:20 by phiascha          #+#    #+#             */
/*   Updated: 2025/06/14 14:24:45 by phiascha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_error(char *str)
{
	write(2, str, ft_strlen(str));
}

void	print_error_cmd(char *str)
{
	print_error(str);
	print_error(": command not found\n");
}

void	print_error_tok(t_token_type type)
{
	print_error("syntax error near unexpected token '");
	if (type == TK_REDIR_IN)
		write(2, "<", 1);
	else if (type == TK_REDIR_OUT)
		write(2, ">", 1);
	else if (type == TK_REDIR_APPEND)
		write(2, ">>", 2);
	else if (type == TK_HEREDOC)
		write(2, "<<", 2);
	else
		write(2, "|", 1);
	write(2, "'\n", 2);
}
