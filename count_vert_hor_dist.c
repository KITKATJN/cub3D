#include "cub3D.h"

void horizontal_intersaction(t_all *all, float curr_ray, t_inter *inter)
{
	int y;
	int minus_y;
	int minus_x;

	minus_x = 1;
	minus_y = 1;
	if (curr_ray > 2 * M_PI)
		curr_ray -= 2 * M_PI;
	if (curr_ray < 0)
		curr_ray += 2 * M_PI;
	if (sin(curr_ray) < 0)
	{
		y = (int)ceilf(all->plr->y / SCALE);//смотри вниз
		inter->y_error = (float)0;
	}
	else
	{
		y = (int)floorf(all->plr->y / SCALE);
		inter->y_error = (float)(-0.001);
		minus_y *= -1;
	}
	if (cos(curr_ray) < 0)
		minus_x *= -1;
	inter->y_hor = all->plr->y / SCALE + minus_y * fabsf(all->plr->y / SCALE - (float)y);
	inter->x_hor = all->plr->x / SCALE + minus_x * fabsf(all->plr->y / SCALE - (float)y) / fabsf(tanf(curr_ray));
	while ((int)inter->x_hor > 0 && (int)inter->x_hor < (int)ft_strlen(all->map[0]))
	{
		if (all->map[(int)(inter->y_hor + inter->y_error)][(int)inter->x_hor] == '1')
			break ;
		inter->y_hor += minus_y;
		inter->x_hor += minus_x / fabsf(tanf(curr_ray));
	}
	inter->hor_dist = ((inter->x_hor - all->plr->x / SCALE)) * (cosf(all->plr->dir)) + ((all->plr->y / SCALE - inter->y_hor)) * (sinf(all->plr->dir));
}


void vert_intersaction(t_all *all, float curr_ray, t_inter *inter)
{
	int x;
	int minus_x;
	int minus_y;

	minus_x = 1;
	minus_y = 1;

	if (curr_ray > 2 * M_PI)
		curr_ray -= 2 * M_PI;
	if (curr_ray < 0)
		curr_ray += 2 * M_PI;
	if (cos(curr_ray) < 0)
	{
		x = (int)floorf(all->plr->x / SCALE);
		minus_x *= -1;
		inter->x_error = (float)(-0.001);
	}
	else
	{
		x = (int)ceilf(all->plr->x / SCALE);
		inter->x_error = (float)(0);
	}
	if (sin(curr_ray) > 0)
	{
		minus_y *= -1;
	}

	inter->x_vert = all->plr->x / SCALE + minus_x * fabsf(all->plr->x / SCALE - (float)x);
	inter->y_vert = all->plr->y / SCALE + minus_y * fabsf(all->plr->x / SCALE - (float)x) * fabsf(tanf((curr_ray )));
	while ((int)inter->y_vert > 0 && (int)inter->y_vert < all->map_height) //вместо 20 должно быть ограничение по высоте карты или тип того
	{
		//printf("y_vert = %d\n", (int)inter->y_vert);
		if (all->map[(int)(inter->y_vert)][(int)(inter->x_vert + inter->x_error)] == '1')
			break ;
		inter->x_vert += minus_x ;
		inter->y_vert += minus_y * fabsf(tanf((curr_ray)));
	}
	inter->vert_dist = ((inter->x_vert - all->plr->x / SCALE)) * (cosf(all->plr->dir)) + ((all->plr->y / SCALE - inter->y_vert)) * (sinf(all->plr->dir));
}

