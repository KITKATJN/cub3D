# ifndef CUB3D_H
# define CUB3D_H

#include "./libft/libft.h"
#include "./get_next_line/get_next_line.h"
#include <fcntl.h>
#include <mlx.h>
#include <math.h>

# define SCALE	4 // условный размер каждого квадратика в карте
# define RES_X	800
# define RES_Y	600

typedef struct	s_win //структура для окна
{
	void		*mlx;
	void		*win;
	void		*img;
	void		*wall_img;
	void		*addr;
	void		*wall_addr;
	char		*relative_path;
	int			img_width;
	int			img_height;
	int			line_l;
	int			wall_bpp;
	int			wall_line_length;
	int			bpp;
	int			en;
}				t_win;

typedef struct	s_point // структура для точки
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_inter // структура для точки
{
	float		x_vert;
	float		y_vert;
	float		x_hor;
	float		y_hor;
	float		vert_dist;
	float		hor_dist;
	float		y_error;
	float		x_error;
	float		wall_height;
}				t_inter;

typedef struct	s_plr //структура для игрока и луча
{
	float		x;
	float		y;
	float		dir;
	float		start;
	float		end;
}				  t_plr;

typedef struct	s_all // структура для всего вместе
{
	t_win		*win;
	t_plr		*plr;
	char		**map;
}				t_all;

void			ft_draw_pixel_ray(t_win *window, int i, int j, int color);
void			pixel_put(t_win *win, int x, int y, int color);
void			ft_draw_player2(t_all *all, t_plr *pl);
void			vert_intersaction(t_all *all, float curr_ray, t_inter *inter);
void			horizontal_intersaction(t_all *all, float curr_ray, t_inter *inter);
int				get_color(t_win *win, int x, int y);
void			my_mlx_pixel_put(t_win *win, int x, int y, int color);

#endif
