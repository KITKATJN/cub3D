# ifndef CUB3D_H
# define CUB3D_H

#include "./libft/libft.h"
#include "./get_next_line/get_next_line.h"
#include <fcntl.h>
#include <mlx.h>
#include <math.h>
#include <stdio.h>

# define SCALE	1 // условный размер каждого квадратика в карте
# define FOV  M_PI / 3
# define SPEED 0.4
# define VALID_MAP_SYMB " 012NESW"
# define VALID_FC_SYMB " 0123456789,	"
# define VALID_R_SYMB " 0123456789	"
# define MAX_INT	"2147483647"
typedef struct	s_win //структура для окна
{
	void		*mlx;
	void		*win;
	void		*img;
	void		*SO_img;
	void		*NO_img;
	void		*WE_img;
	void		*EA_img;
	void		*S_img;
	void		*wall_img;
	void		*addr;
	void		*SO_addr;
	void		*NO_addr;
	void		*WE_addr;
	void		*EA_addr;
	void		*S_addr;
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
	int			S_height;
	int			S_width;
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
	int			S_bpp;
	int			S_line_length;
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

typedef struct	s_texture
{
	float		ty;
	float		tx;
	float		ty_off;
	float		ty_step;
	float		res_y;
	int			clr;
	int			start;
	int			end;
	int			cor_x;
}				t_texture;

typedef struct	s_inter // структура для точки
{
	int			hit;
	float		x;
	float		y;
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
	float		*depthBuffer;
}				t_all;

typedef struct	s_drawsprite
{
	float		angle1;
	float		angle2;
	float		ang;
	float		fobjCeil;
	float		fobjFloor;
	float		fobjHeight;
	float		fObjAspectRatio;
	float		fObjWidth;
	float		fMiddleObj;
	float		lx;
	float		ly;
	float		fSamplex;
	float		fSampley;
	int			nObjColumn;
	int			color_spr;
}				t_drawsprite;

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
void			ft_perror(char *error);
void			ft_screen_shot(t_all *all);
void			ft_draw_wall(t_all *all, t_inter *inter, int cor_x, float ray);
void			ft_set_hor_param(t_all *all, t_inter *inter, float ray);
void			ft_set_vert_param(t_all *all, t_inter *inter, float ray);
int				get_color(t_win *win, int x, int y);
int				get_color_s(t_win *win, int x, int y);
void			my_mlx_pixel_put(t_win *win, int x, int y, int color);
void			ft_paint_sprite(t_all *all, t_drawsprite *drspr, int i);
void			ft_paint_spr(t_all *all, t_drawsprite *drspr, int i);
void			ft_draw_sprite(t_all *all, float angle);
void			ft_sort_sprite(t_all *all);
#endif
