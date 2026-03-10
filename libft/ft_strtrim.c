/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiascha <phiascha@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:54:03 by phiascha          #+#    #+#             */
/*   Updated: 2024/10/14 17:54:06 by phiascha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	measure_trim(char const *s1, char const *set, int is_end)
{
	size_t	output;
	size_t	i;

	output = 0;
	while (output < ft_strlen(s1))
	{
		i = 0;
		while (i < ft_strlen(set))
		{
			if (is_end == 0 && s1[output] == set[i])
				break ;
			if (is_end == 1 && s1[ft_strlen(s1) - output - 1] == set[i])
				break ;
			i++;
		}
		if (i == ft_strlen(set))
			break ;
		output++;
	}
	return (output);
}

char	*ft_get_result(char const *s1, size_t beginning, size_t end)
{
	char	*result;
	size_t	i;

	result = malloc(sizeof(char) * (ft_strlen(s1) - beginning - end + 1));
	if (!result)
		return (0);
	i = 0;
	while (i < ft_strlen(s1) - beginning - end)
	{
		result[i] = s1[beginning + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	beginning;
	size_t	end;

	if (!s1)
		return (0);
	if (!set)
		return ((char *)s1);
	beginning = measure_trim(s1, set, 0);
	if (beginning == ft_strlen(s1))
		return (ft_get_result(s1, beginning, 0));
	end = measure_trim(s1, set, 1);
	return (ft_get_result(s1, beginning, end));
}
