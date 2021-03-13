/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_img_param.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 12:25:38 by cmarguer          #+#    #+#             */
/*   Updated: 2021/03/13 12:26:44 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_set_hor_param(t_all *all, t_inter *inter, float ray)
{
	inter->hit = 0;
	inter->x = inter->x_hor;
	inter->y = inter->y_hor;
	if (sin(ray) > 0)
	{
		all->win->img_height = all->win->EA_height;
		all->win->img_width = all->win->EA_width;
		all->win->wall_bpp = all->win->EA_bpp;
		all->win->wall_line_length = all->win->EA_line_length;
		all->win->wall_addr = all->win->EA_addr;
	}
	else
	{
		all->win->img_height = all->win->WE_height;
		all->win->img_width = all->win->WE_width;
		all->win->wall_bpp = all->win->WE_bpp;
		all->win->wall_line_length = all->win->WE_line_length;
		all->win->wall_addr = all->win->WE_addr;
	}
}

void	ft_set_vert_param(t_all *all, t_inter *inter, float ray)
{
	inter->hit = 1;
	inter->x = inter->x_vert;
	inter->y = inter->y_vert;
	if (cos(ray) > 0)
	{
		all->win->img_height = all->win->SO_height;
		all->win->img_width = all->win->SO_width;
		all->win->wall_bpp = all->win->SO_bpp;
		all->win->wall_line_length = all->win->SO_line_length;
		all->win->wall_addr = all->win->SO_addr;
	}
	else
	{
		all->win->img_height = all->win->NO_height;
		all->win->img_width = all->win->NO_width;
		all->win->wall_bpp = all->win->NO_bpp;
		all->win->wall_line_length = all->win->NO_line_length;
		all->win->wall_addr = all->win->NO_addr;
	}
}
