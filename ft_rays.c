#include "cub3D.h"

int	get_color(t_win *win, int x, int y)
{
	char	*dst;
	int		color;

	dst = win->wall_addr + (x * (win->wall_bpp / 8) + y * win->wall_line_length);
	color = *(unsigned int*)dst;
	return (color);
}

void my_mlx_pixel_put(t_win *win, int x, int y, int color)
{
	char *dst;
	//printf("all = %d  x  = %d bpp = %d y * line_l = %d y = %d line_ l = %d\n", (y * win->line_l + x * (win->bpp / 8)), (x ) , win->bpp, y * win->line_l, y, win->line_l);
	if (x < 0 || y < 0)
		return ;
	//((int*)win->addr)[x + y * win->line_l] = color;
	dst = win->addr + (y * win->line_l + x * (win->bpp / 8));
	*(unsigned int*)dst = color;
}

void	ft_draw_wall(t_all *all, t_inter *inter, int cor_x, float ray)
{
	float y;
	float height;

	if (inter->hor_dist > inter->vert_dist)
	{
		height = inter->vert_dist;
		if (cos(ray) > 0)
		{
			all->win->img_height = all->win->SO_height;
			all->win->img_width = all->win->SO_width;
			all->win->wall_bpp = all->win->SO_bpp;
			all->win->wall_line_length = all->win->SO_line_length;
			all->win->wall_addr = all->win->SO_addr;
		}
		else
		{
			all->win->img_height = all->win->NO_height;
			all->win->img_width = all->win->NO_width;
			all->win->wall_bpp = all->win->NO_bpp;
			all->win->wall_line_length = all->win->NO_line_length;
			all->win->wall_addr = all->win->NO_addr;
		}
	}
	else
	{
		height = inter->hor_dist;
		if (sin(ray) > 0)
		{
			all->win->img_height = all->win->EA_height;
			all->win->img_width = all->win->EA_width;
			all->win->wall_bpp = all->win->EA_bpp;
			all->win->wall_line_length = all->win->EA_line_length;
			all->win->wall_addr = all->win->EA_addr;
		}
		else
		{
			all->win->img_height = all->win->WE_height;
			all->win->img_width = all->win->WE_width;
			all->win->wall_bpp = all->win->WE_bpp;
			all->win->wall_line_length = all->win->WE_line_length;
			all->win->wall_addr = all->win->WE_addr;
		}
	}
	//printf("height = %f hor = %f vert = %f", height, inter->hor_dist , inter->vert_dist);
	if (height < (float)1)
		height = 1;
	height = (int)(all->win->res_y / height);
	y = (all->win->res_y - height) / 2;

	//printf("y = %f res_y = %d hey = %f\n", y, all->win->res_y, height);
	inter->wall_height = height;
	height += y;

	float sky = 0;
	while (sky < y)
		my_mlx_pixel_put(all->win, cor_x, sky++, all->win->F_color);
	float i = 0;
	while(y < height)
	{
		i += all->win->img_height / inter->wall_height;
		if (inter->hor_dist < inter->vert_dist)
			my_mlx_pixel_put(all->win , cor_x, y, get_color(all->win, all->win->img_width * (inter->x_hor - floorf(inter->x_hor)), i));
		else
		{
			my_mlx_pixel_put(all->win, cor_x, y, get_color(all->win, all->win->img_width * (ceilf(inter->y_vert) - inter->y_vert), i));
		}
		y++;
	}
	while (y < all->win->res_y)
		my_mlx_pixel_put(all->win, cor_x, y++, all->win->C_color);
}

void	ft_drawi_pixel_ray(t_win *win, int i, int j, int color)
{
	int	cnt_x = 0;
	int	cnt_y = 0;
	while (cnt_y++ < 1)
	{
		cnt_x = 0;
		while (cnt_x++ < 1)
			my_mlx_pixel_put(win, i + cnt_x, j + cnt_y, color);
	}
}

void	ft_draw_sprite(t_all *all, float angle)
{
	float angle1;
	float angle2;
	float ang;
	int i;

	angle -= 2 * (angle - M_PI_2);
	i = 0;
	//printf("HERE\n");
	while (all->spr[i])
	{
		angle1 = atan2f(all->plr->y / SCALE - all->spr[i]->y,all->plr->x / SCALE - all->spr[i]->x);
		angle2 = atan2f(sinf(angle), cosf(angle));
		//printf("%f ====%f \n",all->plr->x / SCALE , all->spr[i]->x);
		ang = angle2 - angle1;
		if (ang > M_PI)
			ang -= 2 * M_PI;
		else if (ang < -M_PI)
			ang += 2 * M_PI;
		printf("angle%d = %f ang1 = %f ang2 = %f\n", i, (ang), angle1, angle2);
		if (fabs(ang) < M_PI_4)
			printf("risuet x = %f y = %f\n", all->spr[i]->x, all->spr[i]->y);
		i++;
	}
}

void	ft_draw_player2(t_all *all, t_plr *pl)
{
	t_plr	plr = *all->plr;
	t_inter	inter;
	int i = all->win->res_x;

	plr.start = plr.dir - M_PI_4;
	plr.end = plr.dir + M_PI_4;
	while (plr.start < plr.end)
	{
		plr.x = pl->x;
		plr.y = pl->y;
/*
		while (all->map[(int)(plr.y / SCALE)][(int)(plr.x / SCALE)] != '1')
		{
			plr.x += cos(plr.dir);
			plr.y -= sin(plr.dir);
			ft_drawi_pixel_ray(all->win, plr.x, plr.y, 0x0000FF00);
		}*/
		horizontal_intersaction(all, plr.start, &inter);
		vert_intersaction(all, plr.start, &inter);
		ft_draw_wall(all, &inter, i--, plr.start);
		if (inter.hor_dist < 0 || inter.vert_dist < 0)
			printf("delete this\n");//
		plr.start += M_PI_2 / all->win->res_x;
	}
	ft_draw_sprite(all, plr.dir);
}

void ft_scale_img2(t_win *win, int x, int y, int color)
{
	t_point end;

	end.x = (x + 1) * 1;
	end.y = (y + 1) * 1;
	x *= 1;
	y *= 1;
	while (y < end.y)
	{
		while (x < end.x)
		{
			mlx_pixel_put(win->mlx, win->win, x++, y, color);
		}
		x -= 1;
		y++;
	}
}

void horizontal_intersaction(t_all *all, float curr_ray, t_inter *inter)
{
	int y;
	int minus_y;
	int minus_x;

	minus_x = 1;
	minus_y = 1;
	if (curr_ray > 2 * M_PI)
		curr_ray -= 2 * M_PI;
	if (curr_ray < 0)
		curr_ray += 2 * M_PI;
	if (sin(curr_ray) < 0)
	{
		y = (int)ceilf(all->plr->y / SCALE);//смотри вниз
		inter->y_error = (float)0;
	}
	else
	{
		y = (int)floorf(all->plr->y / SCALE);
		inter->y_error = (float)(-0.001);
		minus_y *= -1;
	}
	if (cos(curr_ray) < 0)
		minus_x *= -1;
	inter->y_hor = all->plr->y / SCALE + minus_y * fabsf(all->plr->y / SCALE - (float)y);
	inter->x_hor = all->plr->x / SCALE + minus_x * fabsf(all->plr->y / SCALE - (float)y) / fabsf(tanf(curr_ray));
	while ((int)inter->x_hor > 0 && (int)inter->x_hor < (int)ft_strlen(all->map[0]))
	{
		//ft_scale_img2(all->win, inter->x_hor * SCALE, inter->y_hor * SCALE, 0xF0FFFF0F);
		if (all->map[(int)(inter->y_hor + inter->y_error)][(int)inter->x_hor] == '1')
			break ;
		inter->y_hor += minus_y;
		inter->x_hor += minus_x / fabsf(tanf(curr_ray));
	}
	inter->hor_dist = ((inter->x_hor - all->plr->x / SCALE)) * (cosf(all->plr->dir)) + ((all->plr->y / SCALE - inter->y_hor)) * (sinf(all->plr->dir));
}


void vert_intersaction(t_all *all, float curr_ray, t_inter *inter)
{
	int x;
	int minus_x;
	int minus_y;

	minus_x = 1;
	minus_y = 1;

	if (curr_ray > 2 * M_PI)
		curr_ray -= 2 * M_PI;
	if (curr_ray < 0)
		curr_ray += 2 * M_PI;
	if (cos(curr_ray) < 0)
	{
		x = (int)floorf(all->plr->x / SCALE);
		minus_x *= -1;
		inter->x_error = (float)(-0.001);
	}
	else
	{
		x = (int)ceilf(all->plr->x / SCALE);
		inter->x_error = (float)(0);
	}
	if (sin(curr_ray) > 0)
	{
		minus_y *= -1;
	}

	inter->x_vert = all->plr->x / SCALE + minus_x * fabsf(all->plr->x / SCALE - (float)x);
	inter->y_vert = all->plr->y / SCALE + minus_y * fabsf(all->plr->x / SCALE - (float)x) * fabsf(tanf((curr_ray )));
	while ((int)inter->y_vert > 0 && (int)inter->y_vert < 20) //вместо 20 должно быть ограничение по высоте карты или тип того
	{
		if (all->map[(int)(inter->y_vert)][(int)(inter->x_vert + inter->x_error)] == '1')
			break ;
		//ft_scale_img2(all->win, inter->x_vert * SCALE, inter->y_vert * SCALE, 0x000000FF);
		inter->x_vert += minus_x ;
		inter->y_vert += minus_y * fabsf(tanf((curr_ray)));
	}
	//printf("x_vert = %f y_vert = %f pl->x = %f plr->y = %f map = %c ", inter->x_vert, inter->y_vert, all->plr->x / SCALE , all->plr->y / SCALE, all->map[(int)(inter->y_vert)][(int)(inter->x_vert + inter->x_error)]);
	inter->vert_dist = ((inter->x_vert - all->plr->x / SCALE)) * (cosf(all->plr->dir)) + ((all->plr->y / SCALE - inter->y_vert)) * (sinf(all->plr->dir));
}

