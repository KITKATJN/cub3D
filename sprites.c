/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 13:02:42 by cmarguer          #+#    #+#             */
/*   Updated: 2021/03/18 10:16:49 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void				ft_sort_sprite(t_all *all)
{
	int				k;
	int				i;
	t_sprite		*sp;

	k = -1;
	while (all->spr[++k])
	{
		all->spr[k]->dist = fabsf(((all->spr[k]->x - all->plr->x))
			* (cosf(all->plr->dir))
			+ ((all->plr->y - all->spr[k]->y)) * (sinf(all->plr->dir)));
			if (all->spr[k]->dist < 2)
				all->spr[k]->dist = sqrtf((all->spr[k]->x - all->plr->x) * (all->spr[k]->x - all->plr->x) + (all->plr->y - all->spr[k]->y) * (all->plr->y - all->spr[k]->y));
	}
	k = -1;
	while (all->spr[++k + 1])
	{
		i = -1;
		while (all->spr[++i + 1])
		{
			if (all->spr[i]->dist < all->spr[i + 1]->dist)
			{
				sp = all->spr[i];
				all->spr[i] = all->spr[i + 1];
				all->spr[i + 1] = sp;
				i = -1;
			}
		}
	}
}

void				ft_paint_spr(t_all *all, t_drawsprite *drspr, int i)
{
	drspr->fSamplex = drspr->lx / drspr->fObjWidth;
	drspr->fSampley = drspr->ly / drspr->fobjHeight;
	drspr->nObjColumn = (int)(drspr->fMiddleObj + drspr->lx -
		(drspr->fObjWidth / 2.0f));
	if (drspr->nObjColumn >= 0 && drspr->nObjColumn < all->win->res_x)
	{
		drspr->color_spr = get_color_s(all->win, drspr->fSamplex *
			all->win->s_height, drspr->fSampley * all->win->s_width);
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
	drspr->fObjAspectRatio = (float)all->win->s_height
		/ (float)all->win->s_width;
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
