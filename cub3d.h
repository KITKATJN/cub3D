/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 02:16:23 by cmarguer          #+#    #+#             */
/*   Updated: 2021/03/20 09:58:41 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <string.h>
# include <errno.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>

# include "mlx/mlx.h"
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"

# define PI 3.14159265359
# define PI_2 1.570796327
# define PI_6 0.523598776
# define PI_3 1.047197551
# define FOV PI_3
# define SPEED 0.35
# define VALID_MAP_SYMB " 012NESW"
# define VALID_FC_SYMB " 0123456789,"
# define VALID_R_SYMB " 0123456789"
# define MAX_INT	"2147483647"

typedef struct	s_win
{
	void		*mlx;
	void		*win;
	void		*img;
	void		*so_img;
	void		*no_img;
	void		*we_img;
	void		*ea_img;
	void		*s_img;
	void		*wall_img;
	void		*addr;
	void		*so_addr;
	void		*no_addr;
	void		*we_addr;
	void		*ea_addr;
	void		*s_addr;
	char		*relative_path;
	int			res_x;
	int			res_y;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	char		*s_path;
	int			f_color;
	int			c_color;
	int			so_width;
	int			so_height;
	int			no_width;
	int			no_height;
	int			ea_width;
	int			ea_height;
	int			we_width;
	int			s_height;
	int			s_width;
	int			we_height;
	int			line_l;
	int			so_bpp;
	int			so_line_length;
	int			no_bpp;
	int			no_line_length;
	int			we_bpp;
	int			we_line_length;
	int			ea_bpp;
	int			ea_line_length;
	int			s_bpp;
	int			s_line_length;
	int			bpp;
	int			en;
	int			img_height;
	int			img_width;
	int			wall_bpp;
	int			wall_line_length;
	int			count_2;
	void		*wall_addr;
}				t_win;

typedef struct	s_point
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

typedef struct	s_inter
{
	int			minus_y;
	int			minus_x;
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

typedef struct	s_sprite
{
	float		x;
	float		y;
	float		dist;
}				t_sprite;

typedef struct	s_plr
{
	int			map_x;
	int			map_y;
	int			map_check;
	float		x;
	float		y;
	float		dir;
	float		start;
	float		end;
}				t_plr;

typedef struct	s_all
{
	t_win		*win;
	t_plr		*plr;
	t_sprite	**spr;
	char		**map;
	char		**parcer_map;
	float		*depthbuffer;
	int			map_height;
}				t_all;

typedef struct	s_drawsprite
{
	float		angle1;
	float		angle2;
	float		ang;
	float		fobjceil;
	float		fobjfloor;
	float		fobjheight;
	float		fobjaspectratio;
	float		fobjwidth;
	float		fmiddleobj;
	float		lx;
	float		ly;
	float		fsamplex;
	float		fsampley;
	int			nobjcolumn;
	int			color_spr;
	int			res_x;
	int			res_y;
	float		kef;
}				t_drawsprite;

void			ft_draw_pixel_ray(t_win *window, int i, int j, int color);
void			pixel_put(t_win *win, int x, int y, int color);
void			ft_draw_player2(t_all *all, t_plr *pl);
void			vert_intersaction(t_all *all, float curr_ray, t_inter *inter);
void			horizontal_intersaction(t_all *all,
					float curr_ray, t_inter *inter);
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
void			ft_parcer_no(t_all *all, char *str, int start);
void			ft_parcer_so(t_all *all, char *str, int start);
void			ft_parcer_we(t_all *all, char *str, int start);
void			ft_parcer_ea(t_all *all, char *str, int start);
void			ft_parcer_s(t_all *all, char *str, int start);
void			ft_check_colorf2(char *color);
int				ft_check_max_int(char *color);
void			ft_check_colorf(char *color);
void			ft_check_f(char *f);
void			ft_check_number_of_digit(char *f);
void			ft_parcer_f(t_all *all, char *str, int start);
void			ft_parcer_c(t_all *all, char *str, int start);
void			ft_parcer_map(t_all *all, int i);
void			ft_freemap(char **map);
void			ft_count_2(t_all *all);
void			mlx_get_screen_size(int *width, int *height);
void			ft_check_r(char *r, int j);
void			ft_parcer_r(t_all *all, char *str, int j);
void			ft_preparcer(t_all *all);
void			ft_afterparcer(t_all *all, int parametr);
void			ft_init_plr(char **map, t_plr *plr);
int				key_press(int key, t_all *all);

#endif
