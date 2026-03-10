/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiascha <phiascha@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:49:37 by phiascha          #+#    #+#             */
/*   Updated: 2024/10/14 17:49:41 by phiascha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*casted;

	casted = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		casted[i] = (unsigned char) c;
		i++;
	}
	return (s);
}
