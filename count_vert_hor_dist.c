/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_vert_hor_dist.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 01:57:12 by cmarguer          #+#    #+#             */
/*   Updated: 2021/03/20 02:24:44 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	void	ft_hor_intersaction(t_all *all, t_inter *ntr, int y, float c_r)
{
	ntr->minus_x = 1;
	if (cos(c_r) < 0)
		ntr->minus_x *= -1;
	ntr->y_hor = all->plr->y + ntr->minus_y * fabsf(all->plr->y - (float)y);
	ntr->x_hor = all->plr->x + ntr->minus_x
		* fabsf(all->plr->y - (float)y) / fabsf(tanf(c_r));
	while ((int)ntr->x_hor > 0 && (int)ntr->x_hor < (int)ft_strlen(all->map[0]))
	{
		if (all->map[(int)(ntr->y_hor + ntr->y_error)][(int)ntr->x_hor] == '1')
			break ;
		ntr->y_hor += ntr->minus_y;
		ntr->x_hor += ntr->minus_x / fabsf(tanf(c_r));
	}
	ntr->hor_dist = ((ntr->x_hor - all->plr->x))
		* (cosf(all->plr->dir)) + ((all->plr->y - ntr->y_hor))
			* (sinf(all->plr->dir));
}

void			horizontal_intersaction(t_all *all, float c_r, t_inter *ntr)
{
	int			y;

	ntr->minus_y = 1;
	ntr->minus_x = 1;
	if (c_r > 2 * M_PI)
		c_r -= 2 * M_PI;
	if (c_r < 0)
		c_r += 2 * M_PI;
	if (sin(c_r) < 0)
	{
		y = (int)ceilf(all->plr->y);
		ntr->y_error = (float)0;
	}
	else
	{
		y = (int)floorf(all->plr->y);
		ntr->y_error = (float)(-0.001);
		ntr->minus_y *= -1;
	}
	ft_hor_intersaction(all, ntr, y, c_r);
}

static	void	ft_vert_intersaction(t_all *all, t_inter *ntr, int x, float c_r)
{
	int			minus_y;

	minus_y = 1;
	if (sin(c_r) > 0)
		minus_y *= -1;
	ntr->x_vert = all->plr->x + ntr->minus_x * fabsf(all->plr->x - (float)x);
	ntr->y_vert = all->plr->y + ntr->minus_y
		* fabsf(all->plr->x - (float)x) * fabsf(tanf((c_r)));
	while ((int)ntr->y_vert > 0 && (int)ntr->y_vert < all->map_height)
	{
		if (all->map[(int)(ntr->y_vert)][(int)(ntr->x_vert
			+ ntr->x_error)] == '1')
			break ;
		ntr->x_vert += ntr->minus_x;
		ntr->y_vert += ntr->minus_y * fabsf(tanf((c_r)));
	}
	ntr->vert_dist = ((ntr->x_vert - all->plr->x))
		* (cosf(all->plr->dir)) + ((all->plr->y - ntr->y_vert))
			* (sinf(all->plr->dir));
}

void			vert_intersaction(t_all *all, float c_r, t_inter *ntr)
{
	int			x;

	ntr->minus_x = 1;
	ntr->minus_y = 1;
	if (c_r > 2 * M_PI)
		c_r -= 2 * M_PI;
	if (c_r < 0)
		c_r += 2 * M_PI;
	if (cos(c_r) < 0)
	{
		x = (int)floorf(all->plr->x);
		ntr->minus_x *= -1;
		ntr->x_error = (float)(-0.001);
	}
	else
	{
		x = (int)ceilf(all->plr->x);
		ntr->x_error = (float)(0);
	}
	ft_vert_intersaction(all, ntr, x, c_r);
}
