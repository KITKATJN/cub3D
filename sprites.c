/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 13:02:42 by cmarguer          #+#    #+#             */
/*   Updated: 2021/03/18 22:49:03 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		if (all->spr[k]->dist < 0.7)
			all->spr[k]->dist = sqrtf((all->spr[k]->x
				- all->plr->x) * (all->spr[k]->x - all->plr->x)
					+ (all->plr->y - all->spr[k]->y)
						* (all->plr->y - all->spr[k]->y));
	}
	ft_qsort(all, 0, all->win->count_2 - 1);
}

void				ft_paint_spr(t_all *all, t_drawsprite *drspr, int i)
{
	drspr->fsamplex = drspr->lx / drspr->fobjwidth;
	drspr->fsampley = drspr->ly / drspr->fobjheight;
	drspr->nobjcolumn = (int)(drspr->fmiddleobj + drspr->lx -
		(drspr->fobjwidth / 2.0f));
	if (drspr->nobjcolumn >= 0 && drspr->nobjcolumn < all->win->res_x)
	{
		drspr->color_spr = get_color_s(all->win, drspr->fsamplex *
			all->win->s_height, drspr->fsampley * all->win->s_width);
		if (drspr->color_spr > 1907485 &&
			(all->depthbuffer[all->win->res_x
				- drspr->nobjcolumn]) >=
					(all->spr[i]->dist) && all->spr[i]->dist < 20)
		{
			if (drspr->fobjceil + drspr->ly < all->win->res_y)
				my_mlx_pixel_put(all->win, all->win->res_x
					- drspr->nobjcolumn, drspr->fobjceil
						+ drspr->ly, drspr->color_spr);
		}
	}
}

static	void		ft_pnt_sprite2(t_all *all, t_drawsprite *drspr, int i)
{
	if (all->win->res_x < all->win->res_y)
	{
		drspr->res_x = all->win->res_y;
		drspr->res_y = all->win->res_x;
		drspr->kef = (float)((float)all->win->res_x /
			(float)all->win->res_y) + 0.23 + 0.1 *
				(int)((float)all->win->res_y / (float)all->win->res_x / 2);
	}
	else
		drspr->kef = (float)((float)drspr->res_x / (float)all->win->res_y) /
			10 + 0.74 + 0.2 * (int)((float)all->win->res_x /
				(float)all->win->res_y / 2);
}

void				ft_paint_sprite(t_all *all, t_drawsprite *drspr, int i)
{
	drspr->res_x = all->win->res_x;
	drspr->res_y = all->win->res_y;
	ft_pnt_sprite2(all, drspr, i);
	drspr->fobjceil = (float)(drspr->res_y / 2.0)
		- drspr->res_y / ((float)(all->spr[i]->dist));
	drspr->fobjfloor = drspr->res_y - drspr->fobjceil;
	drspr->fobjheight = (drspr->fobjfloor - drspr->fobjceil) * drspr->kef;
	drspr->fobjaspectratio = (float)all->win->s_height
		/ (float)all->win->s_width;
	drspr->fobjwidth = drspr->fobjheight / drspr->fobjaspectratio;
	drspr->fmiddleobj = (0.5f * (drspr->ang
		/ (FOV / 2.0f)) + 0.5f) * (float)all->win->res_x;
	drspr->lx = -1;
	drspr->ly = -1;
	while (++drspr->lx < drspr->fobjwidth)
	{
		drspr->ly = -1;
		while (++drspr->ly < drspr->fobjheight)
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
