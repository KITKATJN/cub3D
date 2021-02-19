#include "./libft/libft.h"
#include "./get_next_line/get_next_line.h"
#include "cub3D.h"
#include <fcntl.h>
#include <mlx.h>
#include <math.h>

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
				//plr->x = pos.x * SCALE;
				//plr->y = pos.y * SCALE;
				plr->x = 332;
				plr->y = 213;
				plr->dir = 1 * M_PI_2;
			}
			pos.x++;
		}
		pos.y++;
	}
}

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


void ft_draw_plr(t_win *win, t_plr *pl)
{
	t_point end;
	t_plr plr = *pl;

	end.x = plr.x + SCALE;
	end.y = plr.y + SCALE;
	while (plr.y < end.y)
	{
		while (plr.x < end.x)
		{
			mlx_pixel_put(win->mlx, win->win, plr.x++, plr.y, 0x119911);
		}
		plr.x -= SCALE;
		plr.y++;
	}
}

void	ft_draw_pixel(t_win *win, int i, int j, int color)
{
	int	cnt_x = 0;
	int	cnt_y = 0;
	while (cnt_y++ < SCALE)
	{
		cnt_x = 0;
		while (cnt_x++ < SCALE)
			mlx_pixel_put(win->mlx, win->win, i + cnt_x, j + cnt_y, color);
	}
}


void draw_screen(t_all *all)
{
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
	ft_draw_player2(all, all->plr);
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
	}
}


char	**make_map(t_list **head, int size)
{
	char	  **map = ft_calloc(size + 1, sizeof(char *));
	int		  i = -1;
	t_list	*tmp = *head;


	while (tmp)
	{
		map[++i] = ft_strdup(tmp->content);
		tmp = tmp->next;
	}
	ft_lstclear(head, &free);
	i = -1;
	return (map);
}

char **ft_read_map(char *argv1)
{
	char *str = NULL;
	t_list *head = NULL;
	const int fd = open(argv1, O_RDONLY);

	while (get_next_line(fd, &str))
	{
		ft_lstadd_back(&head, ft_lstnew(str));
		str = NULL;
	}
	close(fd);
	ft_lstadd_back(&head, ft_lstnew(str));
	str = NULL;
	return (make_map(&head, ft_lstsize(head)));
}

int key_press(int key, t_all *all)
{
	mlx_clear_window(all->win->mlx, all->win->win);
	if (key == 100)
	{
		all->plr->dir += 0.1;
		if (all->plr->dir > 2 * M_PI)
			all->plr->dir -= 2 * M_PI;
	}
	if (key == 97)
	{
		all->plr->dir -= 0.1;
		if (all->plr->dir < 0)
			all->plr->dir += 2 * M_PI;
	}
	if (key == 119)
	{
		all->plr->y -= sin(all->plr->dir) * 4;
		all->plr->x -= cos(all->plr->dir) * 4;
		if (all->map[(int)all->plr->y / SCALE][(int)all->plr->x / SCALE] == '1')
		{
			all->plr->y += sin(all->plr->dir) * 4;
			all->plr->x += cos(all->plr->dir) * 4;
		}
	}
	if (key == 115)
	{
		all->plr->y += sin(all->plr->dir) * 4;
		all->plr->x += cos(all->plr->dir) * 4;
		//printf("%d**%d\n", (int)all->plr->y / SCALE, (int)all->plr->x / SCALE);
		if (all->map[(int)all->plr->y / SCALE][(int)all->plr->x / SCALE] == '1')
		{
			all->plr->y -= sin(all->plr->dir) * 4;
			all->plr->x -= cos(all->plr->dir) * 4;
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
	win.win = mlx_new_window(win.mlx, 640, 480, "cubik");
	//win.img = mlx_new_image(win.mlx, 640, 480);
	//win.addr = mlx_get_data_addr(win.img, &win.bpp, &win.line_l, &win.en);
	all.plr = &plr;
	all.win = &win;
	draw_screen(&all);
	mlx_hook(win.win, 2, (1L << 0), &key_press, &all);
	mlx_loop(win.mlx);
}
