/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiascha <phiascha@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 00:25:45 by phiascha          #+#    #+#             */
/*   Updated: 2025/06/15 06:22:54 by phiascha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strjoin_substr(char *s1, const char *input, int i)
{
	char	*substr;
	char	*joined;

	substr = ft_substr(input, i, 1);
	if (!substr)
	{
		free(s1);
		return (NULL);
	}
	joined = ft_strjoin(s1, substr);
	free(s1);
	free(substr);
	return (joined);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}

void	remove_str_quotes(char *str)
{
	char	quote;
	size_t	i;
	size_t	len;

	if (str == NULL)
		return ;
	quote = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '"' || str[i] == '\'')
			&& (quote == 0 || quote == str[i]))
		{
			if (quote == 0)
				quote = str[i];
			else
				quote = 0;
			len = ft_strlen(str + i + 1);
			ft_memmove(str + i, str + i + 1, len + 1);
		}
		else
			i++;
	}
}

static bool	create_new_tokens(t_token *tokens, char *expanded)
{
	t_token	*new_tokens;
	t_token	*rest;
	t_token	*next;

	new_tokens = tokenize(expanded);
	free(expanded);
	if (!new_tokens)
	{
		print_error("Malloc error\n");
		return (false);
	}
	rest = tokens->next;
	tokens->type = new_tokens->type;
	tokens->str = new_tokens->str;
	remove_str_quotes(tokens->str);
	next = new_tokens->next;
	while (next)
	{
		tokens->next = next;
		tokens = tokens->next;
		next = next->next;
	}
	tokens->next = rest;
	free(new_tokens);
	return (true);
}

bool	expand2(t_token *tokens, t_data data)
{
	char	*expanded;
	size_t	i;

	expanded = expand_variables(tokens->str, data);
	if (!expanded)
	{
		print_error("Malloc error\n");
		return (false);
	}
	free(tokens->str);
	tokens->str = NULL;
	i = 0;
	while (is_space(expanded[i]))
		i++;
	if (i == ft_strlen(expanded))
	{
		free(expanded);
		return (true);
	}
	return (create_new_tokens(tokens, expanded));
}
