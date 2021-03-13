#include "cub3D.h"

void	ft_sort_sprite(t_all *all)
{
	int k;
	int i;
	t_sprite *sp;

	k = 0;
	while (all->spr[k])
	{
		all->spr[k]->dist = fabsf(((all->spr[k]->x - all->plr->x)) * (cosf(all->plr->dir)) + ((all->plr->y - all->spr[k]->y)) * (sinf(all->plr->dir)));
		k++;
	}
	k = 0;
	i = 0;
	while (all->spr[k + 1])
	{
		i = 0;
		//printf("sf\n");
		while (all->spr[i + 1])
		{
			//printf("ds\n");
			if (all->spr[i]->dist < all->spr[i + 1]->dist)
			{
				sp = all->spr[i];
				all->spr[i] = all->spr[i + 1];
				all->spr[i + 1] = sp;
				i = -1;
			}
			i++;
		}
		k++;
	}
	// k = 0;
	// while (all->spr[k])
	// {
	// 	printf("d = %f y = %f\n", all->spr[k]->dist, all->spr[k]->y);
	// 	k++;
	// 	/* code */
	// }
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
	ft_sort_sprite(all);
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
			if (ft_strchr("N",map[pos.y][pos.x]))
			{
				plr->x = pos.x + 0.5;
				plr->y = pos.y + 0.5;
				plr->dir = 1 * M_PI_2;
			}
			if (ft_strchr("S",map[pos.y][pos.x]))
			{
				plr->x = pos.x + 0.5;
				plr->y = pos.y + 0.5;
				plr->dir = 3 * M_PI_2;
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

	win.NO_img = mlx_xpm_file_to_image(win.mlx, all.win->NO_path, &win.NO_width, &win.NO_height);
	if (!win.NO_img)
		ft_perror("Error with NO_PATH");
	win.NO_addr = mlx_get_data_addr(win.NO_img, &win.NO_bpp, &win.NO_line_length, &win.en);// что будет, если передать в первый параметр 0 или фигню? Какая защита

	win.SO_img = mlx_xpm_file_to_image(win.mlx, all.win->SO_path, &win.SO_width, &win.SO_height);
	if (!win.SO_img)
		ft_perror("Error with SO_PATH");
	win.SO_addr = mlx_get_data_addr(win.SO_img, &win.SO_bpp, &win.SO_line_length, &win.en);

	win.EA_img = mlx_xpm_file_to_image(win.mlx, all.win->EA_path, &win.EA_width, &win.EA_height);
	if (!win.EA_img)
		ft_perror("Error with EA_PATH");
	win.EA_addr = mlx_get_data_addr(win.EA_img, &win.EA_bpp, &win.EA_line_length, &win.en);

	win.WE_img = mlx_xpm_file_to_image(win.mlx, all.win->WE_path, &win.WE_width, &win.WE_height);
	if (!win.WE_img)
		ft_perror("Error with WE_PATH");
	win.WE_addr = mlx_get_data_addr(win.WE_img, &win.WE_bpp, &win.WE_line_length, &win.en);

	win.S_img = mlx_xpm_file_to_image(win.mlx, all.win->S_path, &win.S_width, &win.S_height);
	if (!win.S_img)
		ft_perror("Error with S_PATH");
	win.S_addr = mlx_get_data_addr(win.S_img, &win.S_bpp, &win.S_line_length, &win.en);
	draw_screen(&all);
	if (argc > 2)
	{
		ft_check_argv2(argv[2]);
		ft_screen_shot(&all);
	}
	mlx_hook(win.win, 2, (1L << 0), &key_press, &all);
	mlx_loop(win.mlx);
}


// void	ft_draw_sprite(t_all *all, float angle)
// {
// 	float angle1;
// 	float angle2;
// 	float ang;
// 	int i;

// 	angle -= 2 * (angle - M_PI_2);
// 	i = 0;
// 	while (all->spr[i])
// 	{
// 		angle1 = atan2f(all->plr->y / SCALE - all->spr[i]->y,all->plr->x / SCALE - all->spr[i]->x);
// 		angle2 = atan2f(sinf(angle), cosf(angle));
// 		ang = angle2 - angle1;
// 		if (ang > M_PI)
// 			ang -= 2 * M_PI;
// 		else if (ang < -M_PI)
// 			ang += 2 * M_PI;
// 		if (fabs(ang) < M_PI_4 && all->spr[i]->dist > 1.0f)
// 		{
// 			float fobjCeil = (float)(all->win->res_y / 2.0) - all->win->res_y / ((float)(all->spr[i]->dist));
// 			float fobjFloor = all->win->res_y - fobjCeil;
// 			// float correction = 1.0f;
// 			// if (all->spr[i]->dist > 3)
// 			// 	correction = 0.82;
// 			float fobjHeight = (fobjFloor - fobjCeil) * 0.82;
// 			float fObjAspectRatio = (float)all->win->S_height / (float)all->win->S_width;
// 			float fObjWidth = fobjHeight / fObjAspectRatio;

// 			float fMiddleObj = (0.5f * (ang / (M_PI_2 / 2.0f)) + 0.5f) * (float)all->win->res_x;
// 			float lx = -1;
// 			float ly = -1;
// 							printf("dist = %f \n", all->spr[i]->dist);
// 			while (++lx < fObjWidth)
// 			{
// 				ly = -1;
// 				while (++ly < fobjHeight)
// 				{
// 					float fSamplex = lx / fObjWidth;
// 					float fSampley = ly / fobjHeight;
// 					int nObjColumn = (int)(fMiddleObj + lx - (fObjWidth / 2.0f));
// 					if (nObjColumn >= 0 && nObjColumn < all->win->res_x)
// 					{
// 						int color_spr = get_color_s(all->win, fSamplex * all->win->S_height, fSampley * all->win->S_width);
// 						if (color_spr > 1900000 && (all->depthBuffer[all->win->res_x - nObjColumn]) >= (all->spr[i]->dist))
// 						{
// 							if (fobjCeil + ly < all->win->res_y)
// 								my_mlx_pixel_put(all->win, all->win->res_x - nObjColumn, fobjCeil + ly, color_spr);
// 						}
// 					}
// 				}
// 			}
// 		}
// 			//printf("risuet x = %f y = %f\n", all->spr[i]->x, all->spr[i]->y);
// 		i++;
// 	}
// }
