/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiascha <phiascha@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:48:50 by phiascha          #+#    #+#             */
/*   Updated: 2024/10/14 17:48:54 by phiascha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t			i;
	unsigned char	*s10;
	unsigned char	*s20;

	if (n == 0)
		return (0);
	s10 = (unsigned char *) str1;
	s20 = (unsigned char *) str2;
	i = 0;
	while (s10[i] == s20[i] && i < n - 1)
		i++;
	return (s10[i] - s20[i]);
}
