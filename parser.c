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
	mlx_put_image_to_window(all->win->mlx, all->win->win, all->win->img, 0, 0);
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
		all->plr->dir -= 0.03;
		if (all->plr->dir > 2 * M_PI)
			all->plr->dir -= 2 * M_PI;
	}
	if (key == 97)
	{
		all->plr->dir += 0.03;
		if (all->plr->dir < 0)
			all->plr->dir += 2 * M_PI;
	}
	if (key == 119)
	{
		all->plr->y -= sin(all->plr->dir ) * 0.4;
		all->plr->x += cos(all->plr->dir) * 0.4;
		if (all->map[(int)all->plr->y / SCALE][(int)all->plr->x / SCALE] == '1')
		{
			all->plr->y += sin(all->plr->dir) * 0.4;
			all->plr->x -= cos(all->plr->dir) * 0.4;
		}
	}
	if (key == 115)
	{
		all->plr->y += sin(all->plr->dir) * 0.4;
		all->plr->x -= cos(all->plr->dir) * 0.4;
		if (all->map[(int)all->plr->y / SCALE][(int)all->plr->x / SCALE] == '1')
		{
			all->plr->y -= sin(all->plr->dir) * 0.4;
			all->plr->x += cos(all->plr->dir) * 0.4;
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


	all.plr = &plr;
	all.win = &win;
	if (argc == 2)
		all.parcer_map = ft_read_map(argv[1]);
	else
	{
		ft_putendl_fd("need map", 2);
		return (-1);
	}
	ft_parcer(&all);

	ft_init_plr(all.map, &plr);
	win.mlx = mlx_init();
	win.win = mlx_new_window(win.mlx, all.win->res_x, all.win->res_y, "cub3D");
	win.img = mlx_new_image(win.mlx, all.win->res_x, all.win->res_y);
	win.SO_img = mlx_xpm_file_to_image(win.mlx, all.win->SO_path, &win.SO_width, &win.SO_height);
	win.SO_addr = mlx_get_data_addr(win.SO_img, &win.SO_bpp, &win.SO_line_length, &win.en);

	win.NO_img = mlx_xpm_file_to_image(win.mlx, all.win->NO_path, &win.NO_width, &win.NO_height);
	win.NO_addr = mlx_get_data_addr(win.NO_img, &win.NO_bpp, &win.NO_line_length, &win.en);

	win.WE_img = mlx_xpm_file_to_image(win.mlx, all.win->WE_path, &win.WE_width, &win.WE_height);
	win.WE_addr = mlx_get_data_addr(win.WE_img, &win.WE_bpp, &win.WE_line_length, &win.en);

	win.EA_img = mlx_xpm_file_to_image(win.mlx, all.win->EA_path, &win.EA_width, &win.EA_height);
	win.EA_addr = mlx_get_data_addr(win.EA_img, &win.EA_bpp, &win.EA_line_length, &win.en);

	win.addr = mlx_get_data_addr(win.img, &win.bpp, &win.line_l, &win.en);
	draw_screen(&all);
	mlx_hook(win.win, 2, (1L << 0), &key_press, &all);
	mlx_loop(win.mlx);
return 0;
}
