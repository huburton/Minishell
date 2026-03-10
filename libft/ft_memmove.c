/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiascha <phiascha@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:49:21 by phiascha          #+#    #+#             */
/*   Updated: 2024/10/14 17:49:25 by phiascha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
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
		if (src >= dst)
			casted[i] = char_src[i];
		else
			casted[n - i - 1] = char_src[n - i - 1];
		i++;
	}
	return (dst);
}
