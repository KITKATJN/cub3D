/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 12:50:30 by cmarguer          #+#    #+#             */
/*   Updated: 2021/03/13 12:53:19 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void				ft_paint_spr(t_all *all, t_drawsprite *drspr, int i)
{
	drspr->fSamplex = drspr->lx / drspr->fObjWidth;
	drspr->fSampley = drspr->ly / drspr->fobjHeight;
	drspr->nObjColumn = (int)(drspr->fMiddleObj + drspr->lx -
		(drspr->fObjWidth / 2.0f));
	if (drspr->nObjColumn >= 0 && drspr->nObjColumn < all->win->res_x)
	{
		drspr->color_spr = get_color_s(all->win, drspr->fSamplex *
			all->win->S_height, drspr->fSampley * all->win->S_width);
		if (drspr->color_spr > 1907485 &&
			(all->depthBuffer[all->win->res_x
				- drspr->nObjColumn]) >= (all->spr[i]->dist))
		{
			if (drspr->fobjCeil + drspr->ly < all->win->res_y)
				my_mlx_pixel_put(all->win, all->win->res_x
					- drspr->nObjColumn, drspr->fobjCeil
						+ drspr->ly, drspr->color_spr);
		}
	}
}

void				ft_paint_sprite(t_all *all, t_drawsprite *drspr, int i)
{
	drspr->fobjCeil = (float)(all->win->res_y / 2.0)
		- all->win->res_y / ((float)(all->spr[i]->dist));
	drspr->fobjFloor = all->win->res_y - drspr->fobjCeil;
	drspr->fobjHeight = (drspr->fobjFloor - drspr->fobjCeil) * 0.89;
	drspr->fObjAspectRatio = (float)all->win->S_height
		/ (float)all->win->S_width;
	drspr->fObjWidth = drspr->fobjHeight / drspr->fObjAspectRatio;
	drspr->fMiddleObj = (0.5f * (drspr->ang
		/ (FOV / 2.0f)) + 0.5f) * (float)all->win->res_x;
	drspr->lx = -1;
	drspr->ly = -1;
	while (++drspr->lx < drspr->fObjWidth)
	{
		drspr->ly = -1;
		while (++drspr->ly < drspr->fobjHeight)
			ft_paint_spr(all, drspr, i);
	}
}

void				ft_draw_sprite(t_all *all, float angle)
{
	t_drawsprite	drawspr;
	int				i;

	angle -= 2 * (angle - M_PI_2);
	i = 0;
	while (all->spr[i])
	{
		drawspr.angle1 = atan2f(all->plr->y -
			all->spr[i]->y, all->plr->x - all->spr[i]->x);
		drawspr.angle2 = atan2f(sinf(angle), cosf(angle));
		drawspr.ang = drawspr.angle2 - drawspr.angle1;
		if (drawspr.ang > M_PI)
			drawspr.ang -= 2 * M_PI;
		else if (drawspr.ang < -M_PI)
			drawspr.ang += 2 * M_PI;
		if (fabs(drawspr.ang) < (FOV / 0.9) && all->spr[i]->dist > 1.0f)
			ft_paint_sprite(all, &drawspr, i);
		i++;
	}
}

void				ft_draw_player2(t_all *all, t_plr *pl)
{
	t_plr			plr;
	t_inter			inter;
	int				i;

	plr = *all->plr;
	i = all->win->res_x;
	all->depthBuffer = ft_calloc(sizeof(float), all->win->res_x);
	plr.start = plr.dir - FOV / 2;
	plr.end = plr.dir + FOV / 2;
	while (plr.start < plr.end)
	{
		plr.x = pl->x;
		plr.y = pl->y;
		horizontal_intersaction(all, plr.start, &inter);
		vert_intersaction(all, plr.start, &inter);
		ft_draw_wall(all, &inter, i--, plr.start);
		plr.start += FOV / all->win->res_x;
	}
	ft_draw_sprite(all, plr.dir);
}
