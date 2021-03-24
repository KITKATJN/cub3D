/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 08:00:53 by cmarguer          #+#    #+#             */
/*   Updated: 2020/11/12 08:00:55 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	i;
	t_list	*list;

	if (lst == 0)
		return (0);
	i = 1;
	list = lst;
	while (list->next != 0)
	{
		list = list->next;
		i++;
	}
	return (i);
}
