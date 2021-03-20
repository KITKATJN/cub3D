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
	ft_freemap(all->parcer_map);
	if (!all->depthbuffer)
	{
		free(all->depthbuffer);
		all->depthbuffer = 0;
	}
	ft_freespr(all->spr);
}

void			ft_freespr(t_sprite **spr)
{
	int i;

	if (spr != 0)
	{
		i = 0;
		while (spr[i])
		{
			if (spr[i] != 0)
				free(spr[i]);
			spr[i] = 0;
			i++;
		}
		free(spr);
		spr = 0;
	}
}

void			ft_freemap(char **map)
{
	int i;

	if (map != 0)
	{
		i = 0;
		while (map[i])
		{
			if (map[i] != 0)
				free(map[i]);
			map[i] = 0;
			i++;
		}
		free(map);
		map = 0;
	}
}
