#include "cub3D.h"

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
	ft_sort_sprite(all);
	ft_draw_player2(all, all->plr);
	mlx_put_image_to_window(all->win->mlx, all->win->win, all->win->img, 0, 0);
	//mlx_destroy_image(all->win->mlx, all->win->img);
}

void ft_plr_check(t_plr *plr)
{
	if (plr->x == -1)
		return ;
	else
		ft_perror("Redefinition plr!");
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
				if (ft_strchr("N",map[pos.y][pos.x]))
				{
					ft_plr_check(plr);
					plr->x = pos.x + 0.5;
					plr->y = pos.y + 0.5;
					plr->dir = 1 * M_PI_2;
				}
				if (ft_strchr("S",map[pos.y][pos.x]))
				{
					ft_plr_check(plr);
					plr->x = pos.x + 0.5;
					plr->y = pos.y + 0.5;
					plr->dir = 3 * M_PI_2;
				}
				if (ft_strchr("W",map[pos.y][pos.x]))
				{
					ft_plr_check(plr);
					plr->x = pos.x + 0.5;
					plr->y = pos.y + 0.5;
					plr->dir = M_PI;
				}
				if (ft_strchr("E",map[pos.y][pos.x]))
				{
					ft_plr_check(plr);
					plr->x = pos.x + 0.5;
					plr->y = pos.y + 0.5;
					plr->dir = 0;
				}
				pos.x++;
		}
		pos.y++;
	}
}


int ft_wall_collision1(t_all *all, float start_y, float start_x, float back_or_forward)
{
	float dist;
	t_inter inter;

	dist = sqrtf((start_x - all->plr->x) * (start_x - all->plr->x) + (start_y - all->plr->y) * (start_y - all->plr->y));
	all->plr->dir += back_or_forward;
	horizontal_intersaction(all, all->plr->dir, &inter);
	vert_intersaction(all, all->plr->dir, &inter);
	all->plr->dir -= back_or_forward;
	if (dist < inter.hor_dist && dist < inter.vert_dist)
		return (0);
	return (1);
}

int key_press(int key, t_all *all)
{
	mlx_clear_window(all->win->mlx, all->win->win);
	//printf("key %d \n", key);
	if (key == 100)//здесь надо ходить по стрелочкам, а не wasd  2 linux = 100
	{
		all->plr->dir -= 0.03;
		if (all->plr->dir > 2 * M_PI)
			all->plr->dir -= 2 * M_PI;
	}
	if (key == 97) //  0 97
	{
		all->plr->dir += 0.03;
		if (all->plr->dir < 0)
			all->plr->dir += 2 * M_PI;
	}
	if (key == 119)// 13 119
	{
		all->plr->y -= sin(all->plr->dir ) * SPEED;
		all->plr->x += cos(all->plr->dir) * SPEED;
		if (ft_wall_collision1(all, (all->plr->y + sin(all->plr->dir ) * SPEED), (all->plr->x - cos(all->plr->dir) * SPEED), 0))
		{
			all->plr->y += sin(all->plr->dir) * SPEED;
			all->plr->x -= cos(all->plr->dir) * SPEED;
		}
	}
	if (key == 115) // 1 115
	{
		all->plr->y += sin(all->plr->dir) * SPEED;
		all->plr->x -= cos(all->plr->dir) * SPEED;
		//printf("%d**%d\n", (int)all->plr->y / SCALE, (int)all->plr->x / SCALE);
		if (ft_wall_collision1(all, (all->plr->y - sin(all->plr->dir ) * SPEED), (all->plr->x + cos(all->plr->dir) * SPEED), M_PI))
		{
			all->plr->y -= sin(all->plr->dir) * SPEED;
			all->plr->x += cos(all->plr->dir) * SPEED;
		}
	}
	if (key == 124) // 124
	{
		all->plr->x += sin(all->plr->dir) * SPEED;
		all->plr->y += cos(all->plr->dir) * SPEED;
		//printf("%d**%d\n", (int)all->plr->y / SCALE, (int)all->plr->x / SCALE);
		if (all->map[(int)all->plr->y / SCALE][(int)all->plr->x / SCALE] == '1')
		{
			all->plr->x -= sin(all->plr->dir) * SPEED;
			all->plr->y -= cos(all->plr->dir) * SPEED;
		}
	}
	if (key == 123) // 123
	{
		all->plr->x -= sin(all->plr->dir) * SPEED;
		all->plr->y -= cos(all->plr->dir) * SPEED;
		if (all->map[(int)all->plr->y / SCALE][(int)all->plr->x / SCALE] == '1')
		{
			all->plr->x += sin(all->plr->dir) * SPEED;
			all->plr->y += cos(all->plr->dir) * SPEED;
		}
	}
	if (key == 65307)// 53 65307
		exit(0);
	draw_screen(all);
	return (0);
}

void ft_check_argv2(const char *argv2)
{
	if (ft_strlen(argv2) != 6)
		ft_perror("argv2 is wrong by length");
	if (argv2[0] != '-' || argv2[1] != '-' || argv2[2] != 's' || argv2[3] != 'a' || argv2[4] != 'v' || argv2[5] != 'e')
		ft_perror("argv2 is wrong by symbols");
}

int		main(int argc, char **argv)
{
	t_win win;
	t_plr plr;
	t_all all;

	all.plr = &plr;
	all.win = &win;
	if (argc > 1)
	{
		all.parcer_map = ft_read_map(argv[1]);
	}
	else
	{
		ft_putendl_fd("need map", 2);
		return (-1);
	}
	ft_parcer(&all);
	ft_init_plr(all.map, &plr);
	win.mlx = mlx_init();
	win.win = mlx_new_window(win.mlx, all.win->res_x , all.win->res_y, "cub3D");
	win.img = mlx_new_image(win.mlx, all.win->res_x , all.win->res_y);
	win.addr = mlx_get_data_addr(win.img, &win.bpp, &win.line_l, &win.en);

	win.no_img = mlx_xpm_file_to_image(win.mlx, all.win->no_path, &win.no_width, &win.no_height);
	if (!win.no_img)
		ft_perror("Error with NO_PATH");
	win.no_addr = mlx_get_data_addr(win.no_img, &win.no_bpp, &win.no_line_length, &win.en);// что будет, если передать в первый параметр 0 или фигню? Какая защита

	win.so_img = mlx_xpm_file_to_image(win.mlx, all.win->so_path, &win.so_width, &win.so_height);
	if (!win.so_img)
		ft_perror("Error with SO_PATH");
	win.so_addr = mlx_get_data_addr(win.so_img, &win.so_bpp, &win.so_line_length, &win.en);

	win.ea_img = mlx_xpm_file_to_image(win.mlx, all.win->ea_path, &win.ea_width, &win.ea_height);
	if (!win.ea_img)
		ft_perror("Error with EA_PATH");
	win.ea_addr = mlx_get_data_addr(win.ea_img, &win.ea_bpp, &win.ea_line_length, &win.en);

	win.we_img = mlx_xpm_file_to_image(win.mlx, all.win->we_path, &win.we_width, &win.we_height);
	if (!win.we_img)
		ft_perror("Error with WE_PATH");
	win.we_addr = mlx_get_data_addr(win.we_img, &win.we_bpp, &win.we_line_length, &win.en);

	win.s_img = mlx_xpm_file_to_image(win.mlx, all.win->s_path, &win.s_width, &win.s_height);
	if (!win.s_img)
		ft_perror("Error with S_PATH");
	win.s_addr = mlx_get_data_addr(win.s_img, &win.s_bpp, &win.s_line_length, &win.en);
	draw_screen(&all);
	if (argc > 2)
	{
		ft_check_argv2(argv[2]);
		ft_screen_shot(&all);
	}
	mlx_hook(win.win, 2, (1L << 0), &key_press, &all);
	mlx_loop(win.mlx);
}
