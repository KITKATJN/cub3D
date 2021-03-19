/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 12:22:27 by cmarguer          #+#    #+#             */
/*   Updated: 2021/03/20 02:24:56 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_ceil_floor(t_all *all, float start, float end, int cor_x)
{
	float	y;

	y = 0;
	if ((int)start > all->win->res_y || (int)start < 0)
		return ;
	while (y < start)
	{
		my_mlx_pixel_put(all->win, cor_x, y, all->win->c_color);
		y++;
	}
	y = end;
	while (y < all->win->res_y)
	{
		my_mlx_pixel_put(all->win, cor_x, y, all->win->f_color);
		y++;
	}
}

static void	ft_paint_wall(t_all *all, t_inter *inter, t_texture *text)
{
	float i;

	i = 0;
	while (text->start < text->end)
	{
		if (inter->hor_dist < inter->vert_dist)
			text->clr = get_color(all->win, all->win->img_width *
				(inter->x_hor - floorf(inter->x_hor)), text->ty);
		else
			text->clr = get_color(all->win, all->win->img_width *
				(ceilf(inter->y_vert) - inter->y_vert), text->ty);
		if (text->clr != 0)
			my_mlx_pixel_put(all->win, text->cor_x, text->start, text->clr);
		text->ty += text->ty_step;
		i += all->win->img_height / inter->wall_height;
		text->start++;
	}
}

static void	ft_logic_wall(t_all *all, t_inter *inter, int cor_x, float height)
{
	t_texture	text;

	text.res_y = (float)(all->win->res_y > all->win->res_x ?
		all->win->res_x : all->win->res_y);
	text.start = (text.res_y / 2 - height / 2) < 0 ?
		0 : (text.res_y / 2 - height / 2);
	text.end = (text.res_y / 2 + height / 2) > all->win->res_y ?
		all->win->res_y : (text.res_y / 2 + height / 2);
	text.ty_step = all->win->img_height / (height);
	text.ty_off = 0;
	if (height > text.res_y)
		text.ty_off = (height - text.res_y) / 2.0;
	text.ty = text.ty_off * text.ty_step;
	draw_ceil_floor(all, text.start, text.end, cor_x);
	text.cor_x = cor_x;
	ft_paint_wall(all, inter, &text);
}

void		ft_draw_wall(t_all *all, t_inter *inter, int cor_x, float ray)
{
	float y;
	float height;

	if (inter->hor_dist > inter->vert_dist)
	{
		height = inter->vert_dist;
		ft_set_vert_param(all, inter, ray);
	}
	else
	{
		height = inter->hor_dist;
		ft_set_hor_param(all, inter, ray);
	}
	if (height < 0.01)
		height = 0.01;
	all->depthBuffer[cor_x] = height;
	height = (((float)all->win->res_x / 2) * (1 / tanf(FOV / 2)) / height);
	ft_logic_wall(all, inter, cor_x, height);
}
