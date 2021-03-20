/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 20:47:20 by cmarguer          #+#    #+#             */
/*   Updated: 2021/03/20 09:56:34 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_screen(t_all *all)
{
	ft_sort_sprite(all);
	ft_draw_player2(all, all->plr);
	mlx_put_image_to_window(all->win->mlx, all->win->win, all->win->img, 0, 0);
}

int mouse(int key, t_all *all)
{
	printf("key = %d\n", key);
	exit (0);
	// exit_clean(all);
	// return (OK);
}

void ft_check_argv2(const char *argv2)
{
	if (ft_strlen(argv2) != 6)
		ft_perror("Error\n");
	if (argv2[0] != '-' || argv2[1] != '-' || argv2[2] != 's' || argv2[3] != 'a' || argv2[4] != 'v' || argv2[5] != 'e')
		ft_perror("Error\n");
}

void	ft_set_img(t_all *all, t_win *win)
{
	win->no_img = mlx_xpm_file_to_image(win->mlx, all->win->no_path, &win->no_width, &win->no_height);
	if (!win->no_img)
		ft_perror("Error\n");
	win->no_addr = mlx_get_data_addr(win->no_img, &win->no_bpp, &win->no_line_length, &win->en);// что будет, если передать в первый параметр 0 или фигню? Какая защита
	win->so_img = mlx_xpm_file_to_image(win->mlx, all->win->so_path, &win->so_width, &win->so_height);
	if (!win->so_img)
		ft_perror("Error\n");
	win->so_addr = mlx_get_data_addr(win->so_img, &win->so_bpp, &win->so_line_length, &win->en);
	win->ea_img = mlx_xpm_file_to_image(win->mlx, all->win->ea_path, &win->ea_width, &win->ea_height);
	if (!win->ea_img)
		ft_perror("Error\n");
	win->ea_addr = mlx_get_data_addr(win->ea_img, &win->ea_bpp, &win->ea_line_length, &win->en);
	win->we_img = mlx_xpm_file_to_image(win->mlx, all->win->we_path, &win->we_width, &win->we_height);
	if (!win->we_img)
		ft_perror("Error\n");
	win->we_addr = mlx_get_data_addr(win->we_img, &win->we_bpp, &win->we_line_length, &win->en);
	win->s_img = mlx_xpm_file_to_image(win->mlx, all->win->s_path, &win->s_width, &win->s_height);
	if (!win->s_img)
		ft_perror("Error\n");
	win->s_addr = mlx_get_data_addr(win->s_img, &win->s_bpp, &win->s_line_length, &win->en);
}

int		main(int argc, char **argv)
{
	t_win win;
	t_plr plr;
	t_all all;

	all.plr = &plr;
	all.win = &win;
	if (argc > 1)
		all.parcer_map = ft_read_map(argv[1]);
	else
		ft_perror("Error\n");
	ft_parcer(&all);
	ft_init_plr(all.map, &plr);
	win.mlx = mlx_init();
	win.win = mlx_new_window(win.mlx, all.win->res_x , all.win->res_y, "cub3D");
	win.img = mlx_new_image(win.mlx, all.win->res_x , all.win->res_y);
	win.addr = mlx_get_data_addr(win.img, &win.bpp, &win.line_l, &win.en);
	ft_set_img(&all, &win);
	draw_screen(&all);
	if (argc > 2)
	{
		ft_check_argv2(argv[2]);
		ft_screen_shot(&all);
	}
	mlx_hook(win.win, 2, (1L << 0), &key_press, &all);
	mlx_hook(win.win, 17, 0, &mouse, &all);
	mlx_loop(win.mlx);
}
