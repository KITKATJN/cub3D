/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 15:53:43 by cmarguer          #+#    #+#             */
/*   Updated: 2021/03/20 15:53:45 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				ft_wall_collision1(t_all *all, float start_y,
	float start_x, float back_or_forward)
{
	float		dist;
	t_inter		inter;
	float		dir;

	dist = sqrtf((start_x - all->plr->x) * (start_x - all->plr->x)
		+ (start_y - all->plr->y) * (start_y - all->plr->y));
	dir = all->plr->dir + back_or_forward;
	horizontal_intersaction(all, all->plr->dir, &inter);
	vert_intersaction(all, all->plr->dir, &inter);
	if (dist >= fabsf(inter.hor_dist) || dist >= fabsf(inter.vert_dist))
		return (1);
	horizontal_intersaction(all, dir + FOV / 4, &inter);
	vert_intersaction(all, dir + FOV / 4, &inter);
	if (dist >= fabsf(inter.hor_dist) || dist >= fabsf(inter.vert_dist))
		return (1);
	horizontal_intersaction(all, dir - FOV / 4, &inter);
	vert_intersaction(all, dir - FOV / 4, &inter);
	if (dist >= fabsf(inter.hor_dist) || dist >= fabsf(inter.vert_dist))
		return (1);
	return (0);
}

int				ft_wall_collision2(t_all *all, float start_y,
	float start_x, float back_or_forward)
{
	float	dist;
	t_inter	inter;
	float	dir;

	dist = sqrtf((start_x - all->plr->x) * (start_x - all->plr->x)
		+ (start_y - all->plr->y) * (start_y - all->plr->y));
	dir = all->plr->dir + back_or_forward;
	horizontal_intersaction(all, all->plr->dir, &inter);
	vert_intersaction(all, all->plr->dir, &inter);
	if (dist >= fabsf(inter.hor_dist) || dist >= fabsf(inter.vert_dist))
		return (1);
	return (0);
}

static	void	key1_2(int key, t_all *all)
{
	if (key == 1)
	{
		all->plr->y += sin(all->plr->dir) * SPEED;
		all->plr->x -= cos(all->plr->dir) * SPEED;
		if (ft_wall_collision1(all, all->plr->y - sin(all->plr->dir) *
			SPEED, all->plr->x + cos(all->plr->dir) * SPEED, M_PI)
				|| all->map[(int)all->plr->y][(int)all->plr->x] == '1')
		{
			all->plr->y -= sin(all->plr->dir) * SPEED;
			all->plr->x += cos(all->plr->dir) * SPEED;
		}
	}
	if (key == 2)
	{
		all->plr->x += sin(all->plr->dir) * SPEED;
		all->plr->y += cos(all->plr->dir) * SPEED;
		if (ft_wall_collision2(all, (all->plr->y - cos(all->plr->dir) * SPEED),
			(all->plr->x - sin(all->plr->dir) * SPEED), 3 * M_PI_2)
				|| all->map[(int)all->plr->y][(int)all->plr->x] == '1')
		{
			all->plr->x -= sin(all->plr->dir) * SPEED;
			all->plr->y -= cos(all->plr->dir) * SPEED;
		}
	}
}

static	void	key123(int key, t_all *all)
{
	if (key == 124)
	{
		all->plr->dir -= 0.03;
		if (all->plr->dir > 2 * M_PI)
			all->plr->dir -= 2 * M_PI;
	}
	if (key == 123)
	{
		all->plr->dir += 0.03;
		if (all->plr->dir < 0)
			all->plr->dir += 2 * M_PI;
	}
	if (key == 13)
	{
		all->plr->y -= sin(all->plr->dir) * SPEED;
		all->plr->x += cos(all->plr->dir) * SPEED;
		if (ft_wall_collision2(all, (all->plr->y + sin(all->plr->dir) * SPEED),
			(all->plr->x - cos(all->plr->dir) * SPEED), 0) ||
				all->map[(int)all->plr->y][(int)all->plr->x] == '1')
		{
			all->plr->y += sin(all->plr->dir) * SPEED;
			all->plr->x -= cos(all->plr->dir) * SPEED;
		}
	}
}

int				key_press(int key, t_all *all)
{
	mlx_clear_window(all->win->mlx, all->win->win);
	if (key == 124 || key == 123 || key == 13)
		key123(key, all);
	if (key == 2 || key == 1)
		key1_2(key, all);
	if (key == 0)
	{
		all->plr->x -= sin(all->plr->dir) * SPEED;
		all->plr->y -= cos(all->plr->dir) * SPEED;
		if (all->map[(int)all->plr->y][(int)all->plr->x] == '1')
		{
			all->plr->x += sin(all->plr->dir) * SPEED;
			all->plr->y += cos(all->plr->dir) * SPEED;
		}
	}
	if (key == 53)
	{
		ft_freeall(all);
		exit(0);
	}
	draw_screen(all);
	return (0);
}
