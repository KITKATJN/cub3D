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
	if (all->depthbuffer != 0)
	{
		free(all->depthbuffer);
		all->depthbuffer = 0;
	}
	if (all->win->count_2 > 0)
		ft_freespr(all->spr);
	if (all->win->so_path != 0)
		free(all->win->so_path);
	if (all->win->no_path != 0)
		free(all->win->no_path);
	if (all->win->ea_path != 0)
		free(all->win->ea_path);
	if (all->win->we_path != 0)
		free(all->win->we_path);
	if (all->win->s_path != 0)
		free(all->win->s_path);
	all->win->we_path = 0;
	all->win->no_path = 0;
	all->win->ea_path = 0;
	all->win->so_path = 0;
	all->win->s_path = 0;
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
