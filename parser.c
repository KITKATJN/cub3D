#include "cub3D.h"

void ft_scale_img(t_win *win, t_point point)
{
	t_point end;

	end.x = (point.x + 1) * SCALE;
	end.y = (point.y + 1) * SCALE;
	point.x *= SCALE;
	point.y *= SCALE;
	while (point.y < end.y)
	{
		while (point.x < end.x)
		{
			mlx_pixel_put(win->mlx, win->win, point.x++, point.y, 0x00FF0000);
		}
		point.x -= SCALE;
		point.y++;
	}
}


void draw_screen(t_all *all)
{/*
	t_point point;

	point.y = 0;
	int i = 0;
		while (all->map[point.y])
	{
		point.x = 0;
		while (all->map[point.y][point.x])
		{
			i = 0;
			while (i++ < SCALE)
				mlx_pixel_put(all->win->mlx, all->win->win, point.x * SCALE + i, point.y * SCALE, 0xEEEEEEEE);
			point.x++;
			i++;
		}
		point.y++;
	}

	point.y = 0;i = 0;
		while (all->map[point.y])
	{
		point.x = 0;
		while (all->map[point.y][point.x])
		{
			i = 0;
			while (i++ < SCALE)
				mlx_pixel_put(all->win->mlx, all->win->win, point.x * SCALE, point.y * SCALE + i, 0xEEEEEEEE);
			point.x++;
			i++;
		}
		point.y++;
	}

	ft_bzero(&point, sizeof(t_point));
	while (all->map[point.y])
	{
		point.x = 0;
		while (all->map[point.y][point.x])
		{
			if(all->map[point.y][point.x] == '1')
				ft_scale_img(all->win, point);
			point.x++;
		}
		point.y++;
	}*/
	ft_draw_player2(all, all->plr);
	//mlx_put_image_to_window(all->win->mlx, all->win->win, all->win->img, 0, 0);
	//mlx_destroy_image(all->win->mlx, all->win->img);
}

void ft_init_plr(char **map, t_plr *plr)
{
	t_point pos;

	ft_bzero(&pos, sizeof(t_point));
	while (map[pos.y])
	{
		pos.x = 0;
		while (map[pos.y][pos.x])
		{
			if (ft_strchr("WENS",map[pos.y][pos.x]))
			{
				plr->x = pos.x * SCALE + SCALE / 2;
				plr->y = pos.y * SCALE + SCALE / 2;
				plr->dir = 1 * M_PI_2;
			}
			pos.x++;
		}
		pos.y++;
	}
}


int key_press(int key, t_all *all)
{
	mlx_clear_window(all->win->mlx, all->win->win);
	if (key == 100)//здесь надо ходить по стрелочкам, а не wasd
	{
		all->plr->dir -= 0.1;
		if (all->plr->dir > 2 * M_PI)
			all->plr->dir -= 2 * M_PI;
	}
	if (key == 97)
	{
		all->plr->dir += 0.1;
		if (all->plr->dir < 0)
			all->plr->dir += 2 * M_PI;
	}
	if (key == 119)
	{
		all->plr->y -= sin(all->plr->dir ) * 4;
		all->plr->x += cos(all->plr->dir) * 4;
		if (all->map[(int)all->plr->y / SCALE][(int)all->plr->x / SCALE] == '1')
		{
			all->plr->y += sin(all->plr->dir) * 4;
			all->plr->x -= cos(all->plr->dir) * 4;
		}
	}
	if (key == 115)
	{
		all->plr->y += sin(all->plr->dir) * 4;
		all->plr->x -= cos(all->plr->dir) * 4;
		//printf("%d**%d\n", (int)all->plr->y / SCALE, (int)all->plr->x / SCALE);
		if (all->map[(int)all->plr->y / SCALE][(int)all->plr->x / SCALE] == '1')
		{
			all->plr->y -= sin(all->plr->dir) * 4;
			all->plr->x += cos(all->plr->dir) * 4;
		}
	}
	if (key == 65307)
		exit(0);
	draw_screen(all);
	return (0);
}

int		main(int argc, char **argv)
{
	t_win win;
	t_plr plr;
	t_all all;

	if (argc == 2)
		all.map = ft_read_map(argv[1]);
	else
	{
		ft_putendl_fd("need map", 2);
		return (-1);
	}
	ft_init_plr(all.map, &plr);
	win.mlx = mlx_init();
	win.win = mlx_new_window(win.mlx, RES_X, RES_Y, "cub3D");
	win.img = mlx_new_image(win.mlx, RES_X, RES_Y);
	win.wall_img = mlx_xpm_file_to_image(win.mlx, "pictures/2.xpm", &win.img_width, &win.img_height);
	win.wall_addr = mlx_get_data_addr(win.wall_img, &win.wall_bpp, &win.wall_line_length, &win.en);
	win.addr = mlx_get_data_addr(win.img, &win.bpp, &win.line_l, &win.en);
	all.plr = &plr;
	all.win = &win;
	draw_screen(&all);
	mlx_hook(win.win, 2, (1L << 0), &key_press, &all);
	//mlx_put_image_to_window(win.mlx, win.win, win.img, 0, 0);
	mlx_loop(win.mlx);
}
