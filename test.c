#include "./libft/libft.h"
#include "./get_next_line/get_next_line.h"
#include "cub3D.h"
#include <fcntl.h>
#include <mlx.h>

void pixel_put(t_win *win, int x, int y, int color)
{
	char *dst;

	dst = win->addr + (x * (win->bpp / 8) + y * win->line_l);
	*(int *)dst = color;
}

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

char **ft_make_map(t_list **head, int amount)
{
	t_list *tmp = *head;
	char **map = ft_calloc(amount + 1, sizeof(char*));
	int i = 0;

	while (tmp)
	{
		map[i] = ft_strdup(tmp->content);
		i++;
		tmp = tmp->next;
	}
	i = 0;
	ft_lstclear(head, &free);
	while (map[i])
	{
		ft_putendl_fd(map[i++], 1);
	}
	return (map);
}

//char **ft_read_map(char *av1, t_plr *plr)
char **ft_read_map(char *av1)
{
	char *str = NULL;
	t_list *head = NULL;
	int amount = 0;
	const int fd = open(av1, O_RDONLY);

	while (get_next_line(fd, &str))
	{
		ft_lstadd_back(&head, ft_lstnew(str));
		amount++;
		str = NULL;
	}
	close(fd);
	ft_lstadd_back(&head, ft_lstnew(str));
	str = NULL;
	amount++;
	return (ft_make_map(&head, amount));
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

//more new version
/*
void ft_draw_player(t_all *all, t_plr *pl)
{
	t_plr plr = *all->plr;

	plr.start = plr.dir - M_PI_4;
	plr.end = plr.dir + M_PI_4;
	while (plr.start < plr.end)
	{
		plr.x = pl->x;
		plr.y = pl->y;
		while (all->map[(int)(plr.y / SCALE)][(int)(plr.x / SCALE)] != '1')
		{
			plr.x += cos(plr.dir);
			plr.y += sin(plr.dir);
			pixel_put(all->win, plr.x, plr.y, 0x990099);
		}
		plr.start += M_PI_2 / 640;
	}
}
*/
//void ft_scale_img(t_win *win, t_point point, int color)
void ft_scale_img(t_win *win, t_point point)
{
	t_point end;

	end.x = (point.x + 1) * SCALE;
	end.y = (point.y + 1) * SCALE;
	point.x *= SCALE;
	point.y *= SCALE;
	while (point.y < end.y)
	{
		/*
		while (point.x < end.x)
		{
			pixel_put(win, point.x++, point.y, color);
		}
		*/
		while (point.x < end.x)
		{
			mlx_pixel_put(win->mlx, win->win, point.x++, point.y, 0xFFFFFF);
		}
		point.x -= SCALE;
		point.y++;
	}
}

/*
void draw_screen(t_all *all)
{
	t_point point;
	t_win *win = all->win;

	win->img = mlx_new_image(win->mlx, 640, 480);
	win->addr = mlx_get_data_addr(win->addr, &win->bpp, &win->line_l, &win->en);
	ft_bzero(&point, sizeof(t_point));
	while (all->map[point.y])
	{
		point.x = 0;
		while (all->map[point.y][point.x])
		{
			if(all->map[point.y][point.x] == '1')
				ft_scale_img(all->win, point, 0xFFFFFF);
				point.x++;
		}
		point.y++;
	}
	ft_draw_player(all, all->plr);
	mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
	mlx_destroy_image(win->mlx, win->img);
}
*/

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
}

int key_press(int key, t_all *all)
{
	mlx_clear_window(all->win->mlx, all->win->win);
	if (key == 13)
		all->plr->y -=1;
	if (key == 1)
		all->plr->y +=1;
	if (key == 0)
		all->plr->x -= 1;
	if (key == 2)
		all->plr->x += 1;
	if (key == 53)
		exit(0);
	draw_screen(all);
	return (0);
}

/*
int key_press(int key, t_all *all)
{
	mlx_clear_window(all->win->mlx, all->win->win);
	if (key == 13)
	{
		all->plr->y += sin(all->plr->dir) * 4;
		all->plr->x += cos(all->plr->dir) * 4;
	}
	if (key == 1)
	{
		all->plr->y -= sin(all->plr->dir) * 4;
		all->plr->x -= cos(all->plr->dir) * 4;
	}
	if (key == 0)
		all->plr->dir -= 0.1;
	if (key == 2)
		all->plr->dir += 0.1;
	if (key == 53)
		exit(0);
	draw_screen(all);
	return (0);
}
*/

int main(int argc, char *argv[])
{
	t_win win;
	t_plr plr;
	t_all all;

	if (argc == 2)
		all.map = ft_read_map(argv[1]);
		//all.map = ft_read_map(argv[1], &plr);
	else
	{
		ft_putendl_fd("need map", 2);
		return (-1);
	}
	ft_init_player(all.map, &plr);
	win.mlx = mlx_init();
	win.win = mlx_new_window(win.mlx, 640, 480, "cubik");
	win.img = mlx_new_image(win.mlx, 640, 480);
	win.addr = mlx_get_data_addr(win.addr, &win.bpp, &win.line_l, &win.en);
	all.plr = &plr;
	all.win = &win;
	draw_screen(&all);
	mlx_hook(win.win, 2, (1L << 0), &key_press, &all);
	mlx_loop(win.mlx);
}
