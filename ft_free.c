/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 14:39:44 by cmarguer          #+#    #+#             */
/*   Updated: 2021/03/20 14:39:45 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			ft_freeall(t_all *all)
{
	ft_freemap(all->map);
}

void			ft_freemap(char **map)
{
	int i;

	if (map != 0)
	{
		i = 0;
		while (map[i])
		{
			free(map[i]);
			map[i] = 0;
			i++;
		}
		free(map);
		map = 0;
	}
}
