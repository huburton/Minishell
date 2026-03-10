/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiascha <phiascha@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:53:51 by phiascha          #+#    #+#             */
/*   Updated: 2024/10/14 17:53:55 by phiascha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	len;

	len = ft_strlen(str);
	if (str[len] == (char)c)
		return ((char *)&str[len]);
	while (len > 0)
	{
		if (str[len - 1] == (char)c)
			return ((char *)&str[len - 1]);
		len--;
	}
	return (0);
}
