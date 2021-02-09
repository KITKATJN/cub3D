#include "cub3D.h"
#include <math.h>

void	ft_draw_pixel_ray(t_win *window, int i, int j, int color)
{
	int	cnt_x = 0;
	int	cnt_y = 0;
	while (cnt_y++ < 2)
	{
		cnt_x = 0;
		while (cnt_x++ < 2)
			mlx_pixel_put(window->mlx, window->win, i + cnt_x, j + cnt_y, color);
	}
}

void	ray_trace_x(t_all *all)
{
	t_plr	plr= *all->plr;

	int i = 0;
	while (all->map[(int)(plr.y / SCALE)][(int)(plr.x / SCALE)] != '1')
	{
		plr.x += cos(plr.dir / (M_PI / 3.5));
		plr.y += sin(plr.dir / (M_PI / 3.5));
		if (!i)
			printf("x_ray-> %d<=> %d\n",(int)plr.x, (int)plr.y);
		i++;
		ft_draw_pixel_ray(all->win, plr.x, plr.y, 0x0000CD);
	}
}

void	ray_trace_y(t_all *all)
{
	t_plr	plr= *all->plr;

	while (all->map[(int)(plr.y / SCALE)][(int)(plr.x / SCALE)] != '1')
	{
		plr.x += cos(plr.dir * (M_PI / 3.5));
		plr.y += sin(plr.dir * (M_PI / 3.5));
		ft_draw_pixel_ray(all->win, plr.x, plr.y, 0x0000CD);
	}
}
