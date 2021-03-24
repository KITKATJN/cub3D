/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 07:55:19 by cmarguer          #+#    #+#             */
/*   Updated: 2020/11/12 07:56:52 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*list;
	t_list	*nextl;

	list = *lst;
	while (list)
	{
		nextl = list->next;
		if (del)
			del(list->content);
		free(list);
		list = nextl;
	}
	*lst = 0;
}
