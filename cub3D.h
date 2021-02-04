#ifndef CUB3D_H
#define CUB3D_H

#define SCALE 13 // условный размер каждого квадратика в карте

typedef struct	s_win //структура для окна
{
	void		*mlx;
	void		*win;
	void		*img;
	void		*addr;
	int			line_l;
	int			bpp;
	int			en;
}				t_win;

typedef struct	s_point // структура для точки
{
	int			x;
	int			y;
}				t_point;

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

#endif
