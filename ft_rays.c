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
	while (cnt_y++ < 2)
	{
		cnt_x = 0;
		while (cnt_x++ < 2)
			mlx_pixel_put(win->mlx, win->win, i + cnt_x, j + cnt_y, color);
	}
}

void	ft_draw_player2(t_all *all, t_plr *pl)
{
	t_plr	plr = *all->plr;

	plr.start = plr.dir - M_PI_4;
	plr.end = plr.dir + M_PI_4;
	while (plr.start < plr.end)
	{
		plr.x = pl->x;
		plr.y = pl->y;

		while (all->map[(int)(plr.y / SCALE)][(int)(plr.x / SCALE)] != '1')
		{
			plr.x += cos(plr.start);
			plr.y += sin(plr.start);
			ft_drawi_pixel_ray(all->win, plr.x, plr.y, 0x990099);
		}
		plr.start += M_PI_2 / 640;
	}
}
