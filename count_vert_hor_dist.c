/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_vert_hor_dist.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 15:38:13 by cmarguer          #+#    #+#             */
/*   Updated: 2021/03/20 15:38:14 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	void	ft_hor(t_all *all, float curr_ray, t_inter *inter)
{
	if (cos(curr_ray) < 0)
		inter->minus_x *= -1;
	inter->y_hor = all->plr->y + inter->minus_y *
		fabsf(all->plr->y - (float)inter->mm_y);
	inter->x_hor = all->plr->x + inter->minus_x *
		fabsf(all->plr->y - (float)inter->mm_y) / fabsf(tanf(curr_ray));
	while ((int)inter->x_hor > 0 &&
		(int)inter->x_hor < (int)ft_strlen(all->map[0]))
	{
		if (all->map[(int)(inter->y_hor +
			inter->y_error)][(int)inter->x_hor] == '1')
			break ;
		inter->y_hor += inter->minus_y;
		inter->x_hor += inter->minus_x / fabsf(tanf(curr_ray));
	}
	inter->hor_dist = ((inter->x_hor - all->plr->x)) *
		(cosf(all->plr->dir)) + ((all->plr->y - inter->y_hor))
			* (sinf(all->plr->dir));
}

void			horizontal_intersaction(t_all *all,
	float curr_ray, t_inter *inter)
{
	inter->minus_x = 1;
	inter->minus_y = 1;
	if (curr_ray > 2 * M_PI)
		curr_ray -= 2 * M_PI;
	if (curr_ray < 0)
		curr_ray += 2 * M_PI;
	if (sin(curr_ray) < 0)
	{
		inter->mm_y = (int)ceilf(all->plr->y);
		inter->y_error = (float)0;
	}
	else
	{
		inter->mm_y = (int)floorf(all->plr->y);
		inter->y_error = (float)(-0.001);
		inter->minus_y *= -1;
	}
	ft_hor(all, curr_ray, inter);
}

static	void	ft_vert(t_all *all, float curr_ray, t_inter *inter)
{
	if (sin(curr_ray) > 0)
		inter->minus_y *= -1;
	inter->x_vert = all->plr->x + inter->minus_x *
		fabsf(all->plr->x - (float)inter->mm_x);
	inter->y_vert = all->plr->y + inter->minus_y *
		fabsf(all->plr->x - (float)inter->mm_x) * fabsf(tanf((curr_ray)));
	while ((int)inter->y_vert > 0 && (int)inter->y_vert < all->map_height)
	{
		if (all->map[(int)(inter->y_vert)][(int)(inter->x_vert
			+ inter->x_error)] == '1')
			break ;
		inter->x_vert += inter->minus_x;
		inter->y_vert += inter->minus_y * fabsf(tanf((curr_ray)));
	}
	inter->vert_dist = ((inter->x_vert - all->plr->x)) *
		(cosf(all->plr->dir)) +
			((all->plr->y - inter->y_vert)) * (sinf(all->plr->dir));
}

void			vert_intersaction(t_all *all, float curr_ray, t_inter *inter)
{
	inter->minus_x = 1;
	inter->minus_y = 1;
	if (curr_ray > 2 * M_PI)
		curr_ray -= 2 * M_PI;
	if (curr_ray < 0)
		curr_ray += 2 * M_PI;
	if (cos(curr_ray) < 0)
	{
		inter->mm_x = (int)floorf(all->plr->x);
		inter->minus_x *= -1;
		inter->x_error = (float)(-0.001);
	}
	else
	{
		inter->mm_x = (int)ceilf(all->plr->x);
		inter->x_error = (float)(0);
	}
	ft_vert(all, curr_ray, inter);
}
