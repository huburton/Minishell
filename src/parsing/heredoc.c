/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiascha <phiascha@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:40:47 by phiascha          #+#    #+#             */
/*   Updated: 2025/06/16 21:36:10 by phiascha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*print_error_char(char *str, char *buffer)
{
	free(buffer);
	write(2, str, ft_strlen(str));
	return (NULL);
}

static char	*expand_str(char *buffer, t_data data)
{
	char	*result;
	int		i;

	result = ft_strdup("");
	if (!result)
		return (print_error_char("Malloc error\n", buffer));
	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '$')
		{
			i++;
			result = replace_dollar(result, buffer, &i, data);
		}
		else
			result = ft_strjoin_substr(result, buffer, i++);
		if (!result)
			return (print_error_char("Malloc error\n", buffer));
	}
	free(buffer);
	return (result);
}

static void	print_error_heredoc(char *word)
{
	print_error("warning: here-document delimited by end-of-file (wanted '");
	print_error(word);
	print_error("')\n");
}

static bool	read_stdin(t_data data, int fd, char *word)
{
	char	*buffer;

	while (1)
	{
		buffer = NULL;
		buffer = readline("> ");
		if (!buffer)
		{
			print_error_heredoc(word);
			break ;
		}
		if (!ft_strcmp(word, buffer))
			break ;
		buffer = expand_str(buffer, data);
		if (!buffer)
			return (false);
		write(fd, buffer, ft_strlen(buffer));
		write(fd, "\n", 1);
		free(buffer);
	}
	if (buffer)
		free(buffer);
	close(fd);
	return (true);
}

int	heredoc(t_data data, char *word)
{
	int	fd;

	fd = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		print_error("cannot open heredoc temp file\n");
		return (-1);
	}
	if (!read_stdin(data, fd, word))
	{
		g_signal_status = 0;
		unlink(".heredoc.tmp");
		return (-1);
	}
	g_signal_status = 0;
	fd = open(".heredoc.tmp", O_RDONLY);
	if (fd >= 0)
		unlink(".heredoc.tmp");
	else
		print_error("cannot open heredoc temp file\n");
	return (fd);
}
