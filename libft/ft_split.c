/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiascha <phiascha@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:51:08 by phiascha          #+#    #+#             */
/*   Updated: 2024/10/14 17:51:11 by phiascha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_words(char const *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && str[i] != c)
			count++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (count);
}

char	**ft_free_all(char **tab, int words)
{
	words--;
	while (tab && words >= 0)
	{
		free(tab[words]);
		words--;
	}
	free(tab);
	return (0);
}

char	*get_word(char const *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (ft_substr(str, 0, i));
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i;
	size_t	j;
	int		words;

	if (!s)
		return (0);
	words = count_words(s, c);
	result = malloc((words + 1) * sizeof(char *));
	if (!result)
		return (0);
	i = 0;
	j = 0;
	while (i < words)
	{
		while (s[j] && s[j] == c)
			j++;
		result[i] = get_word(&s[j], c);
		if (!result[i])
			return (ft_free_all(result, i));
		j += ft_strlen(result[i]);
		i++;
	}
	result[i] = 0;
	return (result);
}
