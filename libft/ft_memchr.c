/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiascha <phiascha@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:48:37 by phiascha          #+#    #+#             */
/*   Updated: 2024/10/14 17:48:42 by phiascha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*char_str;

	char_str = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		if (char_str[i] == (unsigned char)c)
			return ((void *) &char_str[i]);
		i++;
	}
	return (0);
}
