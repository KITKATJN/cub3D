/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 07:59:18 by cmarguer          #+#    #+#             */
/*   Updated: 2020/11/12 10:20:03 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list;
	t_list	*copy_list;
	t_list	*new;
	t_list	*head;

	list = lst;
	head = 0;
	copy_list = 0;
	while (list && f)
	{
		new = ft_lstnew(f(list->content));
		if (!new)
		{
			ft_lstclear(&copy_list, del);
			return (0);
		}
		if (head)
			head->next = new;
		head = new;
		if (!copy_list)
			copy_list = head;
		list = list->next;
	}
	return (copy_list);
}
