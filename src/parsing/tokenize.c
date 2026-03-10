/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiascha <phiascha@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:40:34 by phiascha          #+#    #+#             */
/*   Updated: 2025/06/13 18:40:34 by phiascha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token_type	get_token_type(const char *str)
{
	if (ft_strlen(str) >= 2)
	{
		if (!ft_strncmp(str, "<<", 2))
			return (TK_HEREDOC);
		if (!ft_strncmp(str, ">>", 2))
			return (TK_REDIR_APPEND);
	}
	if (!ft_strncmp(str, "<", 1))
		return (TK_REDIR_IN);
	if (!ft_strncmp(str, ">", 1))
		return (TK_REDIR_OUT);
	if (!ft_strncmp(str, "|", 1))
		return (TK_PIPE);
	return (TK_WORD);
}

t_token	*new_token(char *str)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = get_token_type(str);
	if (token->type == TK_WORD)
	{
		token->str = ft_strdup(str);
		if (!token->str)
		{
			free(token);
			return (NULL);
		}
	}
	else
		token->str = NULL;
	token->next = NULL;
	return (token);
}

size_t	word_len(const char *input, size_t i)
{
	int	quote;

	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			quote = i;
			i++;
			while (input[i] && input[i] != input[quote])
				i++;
			if (input[i] == input[quote])
				i++;
		}
		else if (is_space(input[i]) || input[i] == '|'
			|| input[i] == '<' || input[i] == '>')
			break ;
		else
			i++;
	}
	return (i);
}

char	*extract_token(const char *input, size_t *i)
{
	size_t	start;
	size_t	j;
	char	*token;

	start = *i;
	if (input[*i] == '|' || input[*i] == '<' || input[*i] == '>')
	{
		if ((input[*i] == '<' && input[*i + 1] == '<')
			|| (input[*i] == '>' && input[*i + 1] == '>'))
			*i += 2;
		else
			(*i)++;
	}
	else
		*i = word_len(input, *i);
	token = ft_calloc(*i - start + 1, sizeof(char));
	if (!token)
		return (NULL);
	j = 0;
	while (start + j < *i)
	{
		token[j] = input[start + j];
		j++;
	}
	return (token);
}

t_token	*tokenize(const char *input)
{
	t_token	*head;
	size_t	i;
	char	*str;
	t_token	*tok;

	head = NULL;
	i = 0;
	while (input[i])
	{
		while (is_space(input[i]))
			i++;
		if (!input[i])
			break ;
		str = extract_token(input, &i);
		if (!str)
			return (free_tokens(head));
		tok = new_token(str);
		free(str);
		if (!tok)
			return (free_tokens(head));
		append_token(&head, tok);
	}
	return (head);
}
