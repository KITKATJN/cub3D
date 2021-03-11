#include "cub3D.h"

int	get_color(t_win *win, int x, int y)
{
	char	*dst;
	int		color;

	dst = win->wall_addr + (x * (win->wall_bpp / 8) + y * win->wall_line_length);
	color = *(unsigned int*)dst;
	return (color);
}

int	get_color_s(t_win *win, int x, int y)
{
	char	*dst;
	int		color;

	dst = win->S_addr + (x * (win->S_bpp / 8) + y * win->S_line_length);
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

void	draw_ceil_floor(t_all *all, float start, float end, int x)
{
	float	y;

	y = 0;
	if ((int)start > all->win->res_y || (int)start < 0)
		return ;
	//printf("start 22= %d end = %d\n", start, end);
	while (y < start)
	{
		my_mlx_pixel_put(all->win, x, y, all->win->C_color);
		y++;
	}
	y = end;
	while (y < all->win->res_y)
	{
		my_mlx_pixel_put(all->win, x, y, all->win->F_color);
		y++;
	}
}


void	ft_draw_wall(t_all *all, t_inter *inter, int cor_x, float ray)
{
	float y;
	float height;

	if (inter->hor_dist > inter->vert_dist)
	{
		height = inter->vert_dist;
		inter->hit = 1;
		inter->x = inter->x_vert;
		inter->y = inter->y_vert;
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
		inter->hit = 0;
		inter->x = inter->x_hor;
		inter->y = inter->y_hor;
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
	if (height < 0.01)
		height = 0.1;
	all->depthBuffer[cor_x] = height;
	height = (all->win->res_y / height);
	t_texture	text;
	int		start;
	int		end;
	float	res_y;

	res_y = (float)(all->win->res_y > all->win->res_x ? all->win->res_x : all->win->res_y);
	start = (res_y / 2 - height / 2) < 0 ? 0 : (res_y / 2 - height / 2);
	end = (res_y / 2 + height / 2) > all->win->res_y ? all->win->res_y : (res_y / 2 + height / 2);
	text.ty_step = all->win->img_height / (height);
	text.ty_off = 0;
	if (height > res_y)
		text.ty_off = (height - res_y) / 2.0;
	text.ty = text.ty_off * text.ty_step;
	//printf("start = %d end = %d\n", start, end);
	draw_ceil_floor(all, start, end, cor_x);
	float i = 0;
	while (start < end)
	{
		if (inter->hor_dist < inter->vert_dist)
		{
			text.clr = get_color(all->win, all->win->img_width * (inter->x_hor - floorf(inter->x_hor)), text.ty);
			//my_mlx_pixel_put(all->win , cor_x, y, get_color(all->win, all->win->img_width * (inter->x_hor - floorf(inter->x_hor)), i));
		}
		else
		{
			text.clr = get_color(all->win, all->win->img_width * (ceilf(inter->y_vert) - inter->y_vert), text.ty);
			//my_mlx_pixel_put(all->win, cor_x, y, get_color(all->win, all->win->img_width * (ceilf(inter->y_vert) - inter->y_vert), i));
		}
		if (text.clr != 0)
			my_mlx_pixel_put(all->win, cor_x, start, text.clr);
		text.ty += text.ty_step;
		i += all->win->img_height / inter->wall_height;
		start++;
	}
	// //printf("height = %f hor = %f vert = %f", height, inter->hor_dist , inter->vert_dist);
	// float ty_off = 0;
	// all->depthBuffer[cor_x] = height;
	// if (height < 0.01f)
	// 	height = 0.1;
	// //float ty_step = ;
	// height = (all->win->res_y / height);
	// if (height > all->win->res_y)
	// {
	// 	ty_off = (height - all->win->res_y) / 20;
	// 	printf("ty = %f  i = %f\n", ty_off, ty_off * all->win->img_height / inter->wall_height);
	// 	height = all->win->res_y;
	// }

	// y = (all->win->res_y - height) / 2;

	// //printf("y = %f res_y = %d hey = %f\n", y, all->win->res_y, height);
	// inter->wall_height = height;
	// height += y;

	// float sky = 0;
	// while (sky < y)
	// 	my_mlx_pixel_put(all->win, cor_x, sky++, all->win->F_color);
	// float i = 0;
	// while(y < height)
	// {
	// 	if (inter->hor_dist < inter->vert_dist)
	// 		my_mlx_pixel_put(all->win , cor_x, y, get_color(all->win, all->win->img_width * (inter->x_hor - floorf(inter->x_hor)), i));
	// 	else
	// 	{
	// 		my_mlx_pixel_put(all->win, cor_x, y, get_color(all->win, all->win->img_width * (ceilf(inter->y_vert) - inter->y_vert), i));
	// 	}
	// 	i += all->win->img_height / inter->wall_height;
	// 	y++;
	// }
	// while (y < all->win->res_y)
	// 	my_mlx_pixel_put(all->win, cor_x, y++, all->win->C_color);
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


	//printf("draw!!!!!!!!!!!!!\n");
	angle -= 2 * (angle - M_PI_2);
	i = 0;
	while (all->spr[i])
	{
		angle1 = atan2f(all->plr->y / SCALE - all->spr[i]->y,all->plr->x / SCALE - all->spr[i]->x);
		angle2 = atan2f(sinf(angle), cosf(angle));
		ang = angle2 - angle1;
		if (ang > M_PI)
			ang -= 2 * M_PI;
		else if (ang < -M_PI)
			ang += 2 * M_PI;
		if (fabs(ang) < FOV / 2 && all->spr[i]->dist > 1.0f)
		{
			float fobjCeil = (float)(all->win->res_y / 1.8) - all->win->res_y / ((float)(all->spr[i]->dist));
			float fobjFloor = all->win->res_y - fobjCeil;
			float fobjHeight = fobjFloor - fobjCeil;
			float fObjAspectRatio = (float)all->win->S_height / (float)all->win->S_width;
			float fObjWidth = fobjHeight / fObjAspectRatio;

			float fMiddleObj = (0.5f * (ang / (M_PI_2 / 2.0f)) + 0.5f) * (float)all->win->res_x;
			float lx = -1;
			float ly = -1;
			while (++lx < fObjWidth)
			{
				ly = -1;
				while (++ly < fobjHeight)
				{
					float fSamplex = lx / fObjWidth;
					float fSampley = ly / fobjHeight;
					int nObjColumn = (int)(fMiddleObj + lx - (fObjWidth / 2.0f));
					if (nObjColumn >= 0 && nObjColumn < all->win->res_x)
					{
						int color_spr = get_color_s(all->win, fSamplex * all->win->S_height, fSampley * all->win->S_width);
						if (color_spr > 1900000 && (all->depthBuffer[all->win->res_x - nObjColumn]) >= (all->spr[i]->dist))
						{
							if (fobjCeil + ly < all->win->res_y)
							{
								my_mlx_pixel_put(all->win, all->win->res_x - nObjColumn, fobjCeil + ly, color_spr);
							}
						}
					}
				}
			}
		}
			//printf("risuet x = %f y = %f\n", all->spr[i]->x, all->spr[i]->y);
		i++;
	}
}

void	ft_draw_player2(t_all *all, t_plr *pl)
{
	t_plr	plr = *all->plr;
	t_inter	inter;
	int i = all->win->res_x;

	all->depthBuffer = ft_calloc(sizeof(float), all->win->res_x);
	plr.start = plr.dir - FOV / 2;
	plr.end = plr.dir + FOV / 2;
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
		plr.start += FOV / all->win->res_x;
	}
	// i = 0;
	// 		printf("\n\t");
	// while (i < all->win->res_x)
	// {
	// 	printf("h = %f,", all->depthBuffer[i]);
	// 	if (i % 9 == 0)
	// 		printf("\n");
	// 	i++;
	// 	/* code */
	// }
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

