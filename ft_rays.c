#include "cub3D.h"

void	pixel_put(t_win *win, int x, int y, int color)
{
	char *dst;

	dst = win->addr + (x * (win->bpp / 8) + y * win->line_l);
	*(int *)dst = color;
}


void	ft_draw_wall(t_all *all, t_inter inter, int cor_x)
{
	float y;
	float height;
	float sky;

	//int j = 0;

	height = (inter.hor_dist > inter.vert_dist) ? inter.vert_dist : inter.hor_dist;
	height = (int)(RES_Y / height);
	if (height > RES_Y)
		height = RES_Y;
	y = (RES_Y - height) / 2;
	//printf("y = %f height = %f vert = %f hor = %f\n", y, height, inter.vert_dist, inter.hor_dist);
	height += y;
	sky = 0;
	while (sky++ < y)
	{
		mlx_pixel_put(all->win->mlx, all->win->win, cor_x, sky, 0x0066CCFF);
	}

	while(y < height)
	{
	//	if (height < 250)
		mlx_pixel_put(all->win->mlx, all->win->win, cor_x, y, 0xffeebb);
		//	if (height >= 250 && height < 350)
		//mlx_pixel_put(all->win->mlx, all->win->win, cor_x, y, 0xAAAAAAAA);
		//if (height >= 350)
		//	mlx_pixel_put(all->win->mlx, all->win->win, cor_x, y, 0x77777777);
		y++;
	}

	while (y++ < RES_Y)
	{
		mlx_pixel_put(all->win->mlx, all->win->win, cor_x, y, 0x0099ff66);
	}
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
	int i = RES_X - 1;

	plr.start = plr.dir - M_PI_4;
	plr.end = plr.dir + M_PI_4;
	while (plr.start < plr.end)
	{
		plr.x = pl->x;
		plr.y = pl->y;

		while (all->map[(int)(plr.y / SCALE)][(int)(plr.x / SCALE)] != '1')
		{
			plr.x += cos(plr.dir);
			plr.y -= sin(plr.dir);
			//height += sqrt(cos(plr.start)* cos(plr.start) + sin(plr.start) * sin(plr.start));
			ft_drawi_pixel_ray(all->win, plr.x, plr.y, 0x0000FF00);
		}
		inter = horizontal_intersaction(all, plr.start);
		printf("hor1 = %f", inter.hor_dist);
		inter = vert_intersaction(all, plr.start, inter.hor_dist);
		printf("hor2 = %f\n", inter.hor_dist);
		ft_draw_wall(all, inter, i--);
		if (inter.hor_dist < -100)
			printf("delete this\n");
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
		inter.y_error = (float)0;
	}
	else
	{
		y = (int)floorf(all->plr->y / SCALE);
		inter.y_error = (float)(-0.001);
		minus_y *= -1;
	}
	if (cos(curr_ray) < 0)
		minus_x *= -1;
	inter.y = all->plr->y / SCALE + minus_y * fabsf(all->plr->y / SCALE - (float)y);
	inter.x = all->plr->x / SCALE + minus_x * fabsf(all->plr->y / SCALE - (float)y) / fabsf(tanf(curr_ray));
	while ((int)inter.x > 0 && (int)inter.x < (int)ft_strlen(all->map[0]))
	{
		ft_scale_img2(all->win, inter.x * SCALE, inter.y * SCALE, 0xF0FFFF0F);
		if (all->map[(int)(inter.y + inter.y_error)][(int)inter.x] == '1')
			break ;
		inter.y += minus_y;
		inter.x += minus_x / fabsf(tanf(curr_ray));
	}

	float my_dist;
	my_dist = sqrtf(powf((all->plr->x / SCALE - inter.x), 2) + powf((all->plr->y / SCALE - inter.y), 2));
	my_dist *= fabsf(cosf(all->plr->dir - curr_ray));

	inter.hor_dist = ((inter.x - all->plr->x / SCALE)) * (cosf(all->plr->dir)) + ((all->plr->y / SCALE - inter.y)) * (sinf(all->plr->dir));
	//printf("dist = %f my dist = %f\n", inter.hor_dist, my_dist);
	return (inter);
}

t_inter vert_intersaction(t_all *all, float curr_ray, float hor_dist)
{
	t_inter inter;
	int x;
	int minus_x;
	int minus_y;

	inter.hor_dist = hor_dist;
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
		inter.x_error = (float)(-0.001);
	}
	else
	{
		x = (int)ceilf(all->plr->x / SCALE);
		inter.x_error = (float)(0);
	}
	if (sin(curr_ray) > 0)
	{
		minus_y *= -1;
	}

	inter.x = all->plr->x / SCALE + minus_x * fabsf(all->plr->x / SCALE - (float)x);
	inter.y = all->plr->y / SCALE + minus_y * fabsf(all->plr->x / SCALE - (float)x) * fabsf(tanf((curr_ray )));
	while ((int)inter.y > 0 && (int)inter.y < 20) //вместо 20 должно быть ограничение по высоте карты или тип того
	{
		if (all->map[(int)(inter.y)][(int)(inter.x + inter.x_error)] == '1')
			break ;
		ft_scale_img2(all->win, inter.x * SCALE, inter.y * SCALE, 0x000000FF);
		inter.x += minus_x ;
		inter.y += minus_y * fabsf(tanf((curr_ray)));
	}

	float my_dist;
	my_dist = sqrtf(powf((all->plr->x / SCALE - inter.x), 2) + powf((all->plr->y / SCALE - inter.y), 2));
	my_dist *= fabsf(cosf(all->plr->dir - curr_ray));

	inter.vert_dist = ((inter.x - all->plr->x / SCALE)) * (cosf(all->plr->dir)) + ((all->plr->y / SCALE - inter.y)) * (sinf(all->plr->dir));
	//printf("vert dist = %f my dist = %f\n", inter.vert_dist, my_dist);
	return (inter);
}
