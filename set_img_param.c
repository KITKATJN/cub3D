/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_img_param.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 12:25:38 by cmarguer          #+#    #+#             */
/*   Updated: 2021/03/18 10:16:03 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_set_hor_param(t_all *all, t_inter *inter, float ray)
{
	inter->hit = 0;
	inter->x = inter->x_hor;
	inter->y = inter->y_hor;
	if (sin(ray) > 0)
	{
		all->win->img_height = all->win->so_height;
		all->win->img_width = all->win->so_width;
		all->win->wall_bpp = all->win->so_bpp;
		all->win->wall_line_length = all->win->so_line_length;
		all->win->wall_addr = all->win->so_addr;
	}
	else
	{
		all->win->img_height = all->win->no_height;
		all->win->img_width = all->win->no_width;
		all->win->wall_bpp = all->win->no_bpp;
		all->win->wall_line_length = all->win->no_line_length;
		all->win->wall_addr = all->win->no_addr;
	}
}

void	ft_set_vert_param(t_all *all, t_inter *inter, float ray)
{
	inter->hit = 1;
	inter->x = inter->x_vert;
	inter->y = inter->y_vert;
	if (cos(ray) > 0)
	{
		all->win->img_height = all->win->ea_height;
		all->win->img_width = all->win->ea_width;
		all->win->wall_bpp = all->win->ea_bpp;
		all->win->wall_line_length = all->win->ea_line_length;
		all->win->wall_addr = all->win->ea_addr;
	}
	else
	{
		all->win->img_height = all->win->we_height;
		all->win->img_width = all->win->we_width;
		all->win->wall_bpp = all->win->we_bpp;
		all->win->wall_line_length = all->win->we_line_length;
		all->win->wall_addr = all->win->we_addr;
	}
}
