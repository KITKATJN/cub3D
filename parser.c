#include "./libft/libft.h"
#include "./get_next_line/get_next_line.h"
#include "cub3D.h"
#include <fcntl.h>
#include <mlx.h>

void ft_init_player(char **map, t_plr *plr)
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
				plr->x = pos.x * SCALE;
				plr->y = pos.y * SCALE;
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
			mlx_pixel_put(win->mlx, win->win, point.x++, point.y, 0xFFFFFF);
		}
		point.x -= SCALE;
		point.y++;
	}
}


void ft_draw_player(t_win *win, t_plr *pl)
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

void draw_ray_y(t_all *all)
{
	int ray_y;

	ray_y = all->plr->y / SCALE;
	int ray_x = all->plr->x / SCALE;

	int i = 0;
	while (all->map[ray_y][ray_x] != '1')
	{
		//printf("%d", ray_x);
		//printf("=>%c<=%d<=%d\n",all->map[0][0], 0, 0);
		printf("=>%c<=%d<=%d",all->map[ray_y][ray_x], ray_y, ray_x);
		while (i++ < SCALE){
			printf(" work");
			mlx_pixel_put(all->win->mlx, all->win->win, all->plr->x, (ray_y * SCALE) + i, 0x00FF0000);
		}
		printf("\n");
		ray_y--;
		i = 0;
	}
}

void draw_ray_x(t_all *all)
{
	int ray_y;

	ray_y = all->plr->y / SCALE;
	int ray_x = all->plr->x / SCALE;

	int i = 0;
	while (all->map[ray_y][ray_x] != '1')
	{
		while (i++ < SCALE)
			mlx_pixel_put(all->win->mlx, all->win->win, (ray_x * SCALE) + i, all->plr->y, 0x00FF0000);
		ray_x--;
		i = 0;
	}
}

void draw_screen(t_all *all)
{
	t_point point;

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
	}
	ft_draw_player(all->win, all->plr);
	draw_ray_y(all);
	draw_ray_x(all);
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
	//printf("HI");
	//while (map[++i])
	//	ft_putendl_fd(map[i],1);
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
	if (key == 119)
		all->plr->y -= 1;
	if (key == 115)
		all->plr->y += 1;
	if (key == 97)
		all->plr->x -= 1;
	if (key == 100)
		all->plr->x += 1;
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
	ft_init_player(all.map, &plr);
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
