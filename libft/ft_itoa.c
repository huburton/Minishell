/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiascha <phiascha@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:48:21 by phiascha          #+#    #+#             */
/*   Updated: 2024/10/14 17:48:26 by phiascha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nblen(long nb)
{
	int	i;

	i = 0;
	if (nb == 0)
		i = 1;
	if (nb < 0)
	{
		nb *= -1;
		i++;
	}
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long int	nb;
	int			len;
	char		*result;

	nb = (long int)n;
	len = ft_nblen(nb);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (0);
	if (nb < 0)
	{
		result[0] = '-';
		nb *= -1;
	}
	result[len] = '\0';
	if (nb == 0)
		result[0] = '0';
	while (nb > 0)
	{
		result[len - 1] = nb % 10 + '0';
		nb /= 10;
		len--;
	}
	return (result);
}
