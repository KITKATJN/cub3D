#include "cub3D.h"
#include <math.h>

void	pixel_put(t_win *win, int x, int y, int color)
{
	char *dst;

	dst = win->addr + (x * (win->bpp / 8) + y * win->line_l);
	*(int *)dst = color;
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

void	ft_draw_wall(t_all *all, int distToWall, int cor_x)
{
	int i = 0;
	int y;
	//int j = 0;


	if (distToWall == 0)
		distToWall = 1;
	y = 240 - ( 480 / distToWall) / 2;
	//while (j < 8)
	//{
		while(i < ( 480 / distToWall))
		{
			if (distToWall < 5)
				mlx_pixel_put(all->win->mlx, all->win->win, cor_x, y, 0xFFFFFFFF);
			if (distToWall >= 5 && distToWall < 15)
				mlx_pixel_put(all->win->mlx, all->win->win, cor_x, y, 0xAAAAAAAA);
			if (distToWall >= 15)
				mlx_pixel_put(all->win->mlx, all->win->win, cor_x, y, 0x77777777);
			i++;
			y++;
		}
		//cor_x++;
		//j++;
	//}
}

void	ft_draw_player2(t_all *all, t_plr *pl)
{
	t_plr	plr = *all->plr;

	plr.start = plr.dir - M_PI_4;
	plr.end = plr.dir + M_PI_4;

	plr.x = pl->x;
	plr.y = pl->y;
	while (plr.start < plr.end)
	{
		plr.x = pl->x;
		plr.y = pl->y;

		while (all->map[(int)(plr.y / SCALE)][(int)(plr.x / SCALE)] != '1')
		{
			plr.x -= cos(plr.dir);
			plr.y -= sin(plr.dir);
			//distToWall += sqrt(cos(plr.start)* cos(plr.start) + sin(plr.start) * sin(plr.start));
			ft_drawi_pixel_ray(all->win, plr.x, plr.y, 0x990099);
		}



/*
		//printf("%f===", distToWall);
		if ((cos((5 / 4) * M_PI) <= cos(plr.dir) && cos(plr.dir) < cos((7 / 4) * M_PI)) || cos(plr.dir) < cos(M_PI_2 / 2))//up
			curr_dir = 3 * M_PI_2;
		//else if ((((7 / 4) * M_PI < plr.dir) && (plr.dir < (8 / 4) * M_PI)))//right
		//	curr_dir = 2 * M_PI;
		else if (cos((1 / 4) * M_PI) <= cos(plr.dir) && cos(plr.dir) < cos((3 / 4) * M_PI))//down
			curr_dir = M_PI_2;
		else if (cos((3 / 4) * M_PI) <= cos(plr.dir) && cos(plr.dir) < cos((5 / 4) * M_PI))//left
			curr_dir = M_PI;
		distToWall *= fabs(cos(curr_dir - plr.start));
		//printf("%f==cos%f==cur%f==plr.dir%f\n", distToWall, fabs(cos(plr.dir - plr.start)), curr_dir, plr.dir);
		//ft_draw_wall(all, distToWall, cor_x);
		distToWall = 0;
		cor_x++;
		*/

		vert_intersaction(all, plr.start);
		//horizontal_intersaction(all, plr.start);
		plr.start += M_PI_2 / 640;
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

void horizontal_intersaction(t_all *all, float curr_ray)
{
	t_inter inter;
	int y;
	int minus_y;
	int minus_x;

	minus_x = 1;
	minus_y = 1;
	if (sin(curr_ray) < 0)
	{
		y = (int)ceilf(all->plr->y / SCALE);//смотри вниз
	}
	else
	{
		y = (int)floorf(all->plr->y / SCALE);
		minus_y *= -1;
	}
	if (cos(curr_ray) > 0)
		minus_x *= -1;
	inter.y = all->plr->y + minus_y * fabsf(all->plr->y / SCALE - (float)y) * SCALE;
	inter.x = all->plr->x + minus_x * fabsf(all->plr->y / SCALE - (float)y) / tanf(fabsf(curr_ray - all->plr->dir)) * SCALE;
	while ((int)inter.x > 0 && (int)inter.x < (int)ft_strlen(all->map[0]) * SCALE)
	{
		ft_scale_img2(all->win, inter.x, inter.y, 0xF0FFFF0F);
		if (all->map[(int)inter.y / SCALE][(int)inter.x / SCALE] == '1')
			break ;
		inter.y += minus_y * SCALE;
		inter.x += minus_x * SCALE / tanf(fabsf(curr_ray - all->plr->dir));
	}
}

void vert_intersaction(t_all *all, float curr_ray)
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
	inter.y = all->plr->y + minus_y * fabsf(all->plr->x / SCALE - (float)x) * tanf((curr_ray )) * SCALE;
	int i = 1;
	while ((int)inter.y > 0 && (int)inter.y < 20 * SCALE)
	{
		if (all->map[(int)inter.y / SCALE][(int)inter.x / SCALE] == '1')
			break ;
		ft_scale_img2(all->win, inter.x, inter.y, 0x000000FF);
		inter.x += minus_x * SCALE;
		inter.y += minus_y * SCALE * tanf((curr_ray));
		i++;
	}
		//printf("vert = %d\n", i);
}
