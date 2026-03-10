/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiascha <phiascha@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:40:51 by phiascha          #+#    #+#             */
/*   Updated: 2025/06/15 06:16:24 by phiascha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*replace_env(char *result, const char *input, int *i, char **env)
{
	char	*var;
	char	*val;
	int		start;

	start = *i;
	while (ft_isalnum(input[*i]) || input[*i] == '_')
		(*i)++;
	var = ft_substr(input, start, *i - start);
	if (!var)
	{
		free(result);
		return (NULL);
	}
	val = get_env_value(var, env);
	free(var);
	result = ft_strjoin_free(result, val);
	return (result);
}

char	*replace_dollar(char *result, const char *input, int *i, t_data data)
{
	char	*exit_str;

	if (input[*i] == '?')
	{
		exit_str = ft_itoa(data.exit_code);
		if (!exit_str)
		{
			free(result);
			return (NULL);
		}
		result = ft_strjoin_free(result, exit_str);
		free(exit_str);
		(*i)++;
	}
	else if (ft_isalpha(input[*i]) || input[*i] == '_')
		result = replace_env(result, input, i, data.env);
	else
		result = ft_strjoin_free(result, "$");
	return (result);
}

static char	*input_type(char *result, const char *input, int *i, t_data data)
{
	static bool	in_single = false;
	static bool	in_double = false;

	if (*i == 0)
	{
		in_single = false;
		in_double = false;
	}
	if ((input[*i] == '\'' && !in_double)
		|| (input[*i] == '\"' && !in_single))
	{
		if (input[*i] == '\'')
			in_single = !in_single;
		else
			in_double = !in_double;
		result = ft_strjoin_substr(result, input, (*i)++);
	}
	else if (input[*i] == '$' && !in_single)
	{
		(*i)++;
		result = replace_dollar(result, input, i, data);
	}
	else
		result = ft_strjoin_substr(result, input, (*i)++);
	return (result);
}

char	*expand_variables(const char *input, t_data data)
{
	char	*result;
	int		i;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (input[i])
	{
		result = input_type(result, input, &i, data);
		if (!result)
			return (NULL);
	}
	return (result);
}

bool	expand(t_token *tokens, t_data data)
{
	while (tokens)
	{
		if (tokens->type == TK_HEREDOC && tokens->next
			&& tokens->next->type == TK_WORD)
		{
			remove_str_quotes(tokens->next->str);
			tokens = tokens->next;
		}
		else if (tokens->type > 1 && tokens->next
			&& tokens->next->str && tokens->next->str[0] == '$')
			tokens = tokens->next;
		else if (tokens->str)
		{
			if (!expand2(tokens, data))
				return (false);
		}
		tokens = tokens->next;
	}
	return (true);
}
