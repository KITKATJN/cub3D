/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 12:50:30 by cmarguer          #+#    #+#             */
/*   Updated: 2021/03/13 13:01:15 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void				ft_draw_player2(t_all *all, t_plr *pl)
{
	t_plr			plr;
	t_inter			inter;
	int				i;

	plr = *all->plr;
	i = all->win->res_x - 1;
	plr.start = plr.dir - FOV / 2;
	plr.end = plr.dir + FOV / 2;
	while (plr.start < plr.end && i >= 0)
	{
		plr.x = pl->x;
		plr.y = pl->y;
		horizontal_intersaction(all, plr.start, &inter);
		vert_intersaction(all, plr.start, &inter);
		ft_draw_wall(all, &inter, i--, plr.start);
		plr.start += FOV / all->win->res_x;
	}
	if (all->win->count_2 > 0)
		ft_draw_sprite(all, plr.dir);
}
