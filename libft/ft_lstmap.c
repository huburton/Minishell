/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiascha <phiascha@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:58:52 by phiascha          #+#    #+#             */
/*   Updated: 2024/10/14 18:58:53 by phiascha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*new;

	if (!f || !del)
		return (0);
	result = 0;
	while (lst)
	{
		new = ft_lstnew(f(lst->content));
		if (!new)
		{
			while (result)
			{
				new = result->next;
				del(result->content);
				free(result);
				result = new;
			}
			lst = 0;
			return (0);
		}
		ft_lstadd_back(&result, new);
		lst = lst->next;
	}
	return (result);
}
