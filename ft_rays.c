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
	y = 240 - (5 * 480 / distToWall) / 2;
	//while (j < 8)
	//{
		while(i < (5 * 480 / distToWall))
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
	float distToWall;
	int cor_x = 0;

	distToWall = 0;
	plr.start = plr.dir - M_PI_4;
	plr.end = plr.dir + M_PI_4;

	float curr_dir = 3 * M_PI_2;
	plr.x = pl->x;
	plr.y = pl->y;

	while (plr.start < plr.end)
	{
		plr.x = pl->x;
		plr.y = pl->y;
		while (all->map[(int)(plr.y / SCALE)][(int)(plr.x / SCALE)] != '1')
		{
			plr.x += cos(plr.start);
			plr.y += sin(plr.start);
			distToWall++;
			ft_drawi_pixel_ray(all->win, plr.x, plr.y, 0x990099);
		}
		printf("%f===", distToWall);
		if ((5 / 4) * M_PI <= plr.dir && plr.dir < (7 / 4) * M_PI)//up
			curr_dir = 3 * M_PI_2;
		//else if ((((7 / 4) * M_PI < plr.dir) && (plr.dir < (8 / 4) * M_PI)))//right
		//	curr_dir = 2 * M_PI;
		else if ((1 / 4) * M_PI <= plr.dir && plr.dir < (3 / 4) * M_PI)//down
			curr_dir = M_PI_2;
		else if ((3 / 4) * M_PI <= plr.dir && plr.dir < (5 / 4) * M_PI)//left
			curr_dir = M_PI;
		distToWall *= fabs(cos(curr_dir - plr.start));
		printf("%f==%f==cur%f==plr.dir%f\n", distToWall, fabs(cos(plr.dir - plr.start)), curr_dir, plr.dir);
		ft_draw_wall(all, distToWall, cor_x);
		distToWall = 0;
		cor_x++;
		plr.start += M_PI_2 / 640;
	}
}
