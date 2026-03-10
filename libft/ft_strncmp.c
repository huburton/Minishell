/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiascha <phiascha@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:53:22 by phiascha          #+#    #+#             */
/*   Updated: 2024/10/14 17:53:25 by phiascha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s10;
	unsigned char	*s20;

	if (n == 0)
		return (0);
	s10 = (unsigned char *) s1;
	s20 = (unsigned char *) s2;
	i = 0;
	while (s10[i] && s10[i] == s20[i] && i < n - 1)
		i++;
	return (s10[i] - s20[i]);
}
