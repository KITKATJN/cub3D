# ifndef CUB3D_H
# define CUB3D_H

#include "./libft/libft.h"
#include "./get_next_line/get_next_line.h"
#include <fcntl.h>
#include <mlx.h>
#include <math.h>

# define SCALE	4 // условный размер каждого квадратика в карте

typedef struct	s_win //структура для окна
{
	void		*mlx;
	void		*win;
	void		*img;
	void		*SO_img;
	void		*NO_img;
	void		*WE_img;
	void		*EA_img;
	void		*wall_img;
	void		*addr;
	void		*SO_addr;
	void		*NO_addr;
	void		*WE_addr;
	void		*EA_addr;
	char		*relative_path;
	int			res_x;
	int			res_y;
	char		*NO_path;
	char		*SO_path;
	char		*WE_path;
	char		*EA_path;
	char		*S_path;
	int			F_color;
	int			C_color;
	int			SO_width;
	int			SO_height;
	int			NO_width;
	int			NO_height;
	int			EA_width;
	int			EA_height;
	int			WE_width;
	int			WE_height;
	int			line_l;
	int			SO_bpp;
	int			SO_line_length;
	int			NO_bpp;
	int			NO_line_length;
	int			WE_bpp;
	int			WE_line_length;
	int			EA_bpp;
	int			EA_line_length;
	int			bpp;
	int			en;
	int			img_height;
	int			img_width;
	int			wall_bpp;
	int			wall_line_length;
	int			count_2;
	void		*wall_addr;
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

typedef struct	s_sprite //структура для игрока и луча
{
	float		x;
	float		y;
	float		dist;
}				t_sprite;

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
	t_sprite	**spr;
	char		**map;
	char		**parcer_map;

}				t_all;

void			ft_draw_pixel_ray(t_win *window, int i, int j, int color);
void			pixel_put(t_win *win, int x, int y, int color);
void			ft_draw_player2(t_all *all, t_plr *pl);
void			vert_intersaction(t_all *all, float curr_ray, t_inter *inter);
void			horizontal_intersaction(t_all *all, float curr_ray, t_inter *inter);
int				get_color(t_win *win, int x, int y);
void			my_mlx_pixel_put(t_win *win, int x, int y, int color);
char			**make_map(t_list **head, int size);
char			**ft_read_map(char *argv1);
void			ft_parcer(t_all *all);
#endif
