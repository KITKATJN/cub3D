#include "cub3D.h"

void	pixel_put(t_win *win, int x, int y, int color)
{
	char *dst;

	dst = win->addr + (x * (win->bpp / 8) + y * win->line_l);
	*(int *)dst = color;
}


void	ft_draw_wall(t_all *all, t_inter inter, int cor_x)
{
	int y;
	float distToWall;
	int height;

	//int j = 0;

	distToWall = (inter.hor_dist > inter.vert_dist) ? inter.vert_dist : inter.hor_dist;
	height = (int)(RES_Y / distToWall);
	y = (RES_Y - height) / 2;
	//while (j < 8)
	//{
		while(y < height)
		{
			if (distToWall < 5)
				mlx_pixel_put(all->win->mlx, all->win->win, cor_x, y, 0xFFFFFFFF);
			if (distToWall >= 5 && distToWall < 15)
				mlx_pixel_put(all->win->mlx, all->win->win, cor_x, y, 0xAAAAAAAA);
			if (distToWall >= 15)
				mlx_pixel_put(all->win->mlx, all->win->win, cor_x, y, 0x77777777);
			y++;
		}
		//cor_x++;
		//j++;
	//}
}

void	ft_drawi_pixel_ray(t_win *win, int i, int j, int color)
{
	int	cnt_x = 0;
	int	cnt_y = 0;
	while (cnt_y++ < 1)
	{
		cnt_x = 0;
		while (cnt_x++ < 1)
			mlx_pixel_put(win->mlx, win->win, i + cnt_x, j + cnt_y, color);
	}
}

void	ft_draw_player2(t_all *all, t_plr *pl)
{
	t_plr	plr = *all->plr;
	t_inter	inter;
	int i;

	plr.start = plr.dir - M_PI_4;
	plr.end = plr.dir + M_PI_4;
	i = 0;
	while (plr.start < plr.end)
	{
		plr.x = pl->x;
		plr.y = pl->y;

		while (all->map[(int)(plr.y / SCALE)][(int)(plr.x / SCALE)] != '1')
		{
			plr.x += cos(plr.dir);
			plr.y -= sin(plr.dir);
			//distToWall += sqrt(cos(plr.start)* cos(plr.start) + sin(plr.start) * sin(plr.start));
			ft_drawi_pixel_ray(all->win, plr.x, plr.y, 0x0000FF00);
		}
		inter = vert_intersaction(all, plr.start);
		inter = horizontal_intersaction(all, plr.start);
		ft_draw_wall(all, inter, i++);
		plr.start += M_PI_2 / RES_X;
	}
}

void ft_scale_img2(t_win *win, int x, int y, int color)
{
	t_point end;

	end.x = (x + 1) * 1;
	end.y = (y + 1) * 1;
	x *= 1;
	y *= 1;
	while (y < end.y)
	{
		while (x < end.x)
		{
			mlx_pixel_put(win->mlx, win->win, x++, y, color);
		}
		x -= 1;
		y++;
	}
}

t_inter horizontal_intersaction(t_all *all, float curr_ray)
{
	t_inter inter;
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
	}
	else
	{
		y = (int)floorf(all->plr->y / SCALE);
		minus_y *= -1;
	}
	if (cos(curr_ray) < 0)
		minus_x *= -1;
	inter.y = all->plr->y + minus_y * fabsf(all->plr->y / SCALE - (float)y) * SCALE;
	inter.x = all->plr->x + minus_x * fabsf(all->plr->y / SCALE - (float)y) / fabsf(tanf(curr_ray)) * SCALE;
	while ((int)inter.x > 0 && (int)inter.x < (int)ft_strlen(all->map[0]) * SCALE)
	{
		ft_scale_img2(all->win, inter.x, inter.y, 0xF0FFFF0F);
		if (all->map[(int)inter.y / SCALE][(int)inter.x / SCALE] == '1')
			break ;
		inter.y += minus_y * SCALE;
		inter.x += minus_x * SCALE / fabsf(tanf(curr_ray));
	}


	float my_dist;
	my_dist = sqrtf(powf((all->plr->x - inter.x) / SCALE, 2) + powf((all->plr->y - inter.y) / SCALE, 2));
	my_dist *= fabsf(cosf(all->plr->dir - curr_ray));

	inter.hor_dist = ((inter.x - all->plr->x) / SCALE) * (cosf(all->plr->dir)) + ((all->plr->y - inter.y) / SCALE) * (sinf(all->plr->dir));
	//printf("my = %f wolf = %f\n", my_dist, inter.dist);
	if (inter.hor_dist < 0)
		printf("my = %f wolf = %f cos = %f dx = %f  sin = %f dy = %f\n", my_dist, inter.hor_dist, cosf(all->plr->dir), (inter.x - all->plr->x) / SCALE, sinf(all->plr->dir), ((inter.y - all->plr->y) / SCALE));
	if ((int)(my_dist * 100) != (int)(inter.hor_dist * 100))
		printf("my = %f wolf = %f\n", my_dist, inter.hor_dist);
	return (inter);
}

t_inter vert_intersaction(t_all *all, float curr_ray)
{
	t_inter inter;
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
	}
	else
	{
		x = (int)ceilf(all->plr->x / SCALE);
	}
	if (sin(curr_ray) > 0)
	{
		minus_y *= -1;
	}

	inter.x = all->plr->x + minus_x * fabsf(all->plr->x / SCALE - (float)x) * SCALE;
	inter.y = all->plr->y + minus_y * fabsf(all->plr->x / SCALE - (float)x) * fabsf(tanf((curr_ray ))) * SCALE;
	while ((int)inter.y > 0 && (int)inter.y < 20 * SCALE)
	{
		if (all->map[(int)inter.y / SCALE][(int)inter.x / SCALE] == '1')
			break ;
		ft_scale_img2(all->win, inter.x, inter.y, 0x000000FF);
		inter.x += minus_x * SCALE;
		inter.y += minus_y * SCALE * fabsf(tanf((curr_ray)));
	}

	float my_dist;
	my_dist = sqrtf(powf((all->plr->x - inter.x) / SCALE, 2) + powf((all->plr->y - inter.y) / SCALE, 2));
	my_dist *= fabsf(cosf(all->plr->dir - curr_ray));

	inter.vert_dist = ((inter.x - all->plr->x) / SCALE) * (cosf(all->plr->dir)) + ((all->plr->y -inter.y) / SCALE) * (sinf(all->plr->dir));
	return (inter);
}
