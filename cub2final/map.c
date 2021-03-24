/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 16:47:59 by cmarguer          #+#    #+#             */
/*   Updated: 2021/03/20 16:48:00 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char		**make_map(t_all *all, t_list **head, int size)
{
	char	**map;
	int		i;
	t_list	*tmp;

	map = ft_calloc(size + 1, sizeof(char *));
	tmp = *head;
	i = -1;
	while (tmp)
	{
		map[++i] = ft_strdup(tmp->content);
		if (map[i] == 0)
			ft_perror("Error\n with malloc in make map\n", all);
		tmp = tmp->next;
	}
	ft_lstclear(head, &free);
	i = -1;
	return (map);
}

char		**ft_read_map(char *argv1, t_all *all)
{
	char	*str;
	t_list	*head;
	int		fd;
	int		ch;

	str = NULL;
	head = NULL;
	if ((fd = open(argv1, O_RDONLY)) < 0)
		ft_perror("Error\n with open file *.cub\n", all);
	while ((ch = get_next_line(fd, &str)))
	{
		ft_lstadd_back(&head, ft_lstnew(str));
		str = NULL;
	}
	if (ch < 0)
		ft_perror("Error\n with get next line\n", all);
	if (close(fd) < 0)
		ft_perror("Error\n with close file .cub\n", all);
	ft_lstadd_back(&head, ft_lstnew(str));
	str = NULL;
	return (make_map(all, &head, ft_lstsize(head)));
}
