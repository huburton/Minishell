/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiascha <phiascha@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:49:08 by phiascha          #+#    #+#             */
/*   Updated: 2024/10/14 17:49:13 by phiascha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*casted;
	unsigned char	*char_src;

	if (!dst && !src)
		return (0);
	casted = (unsigned char *) dst;
	char_src = (unsigned char *) src;
	i = 0;
	while (i < n)
	{
		casted[i] = char_src[i];
		i++;
	}
	return (dst);
}
