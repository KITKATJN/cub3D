/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 13:02:42 by cmarguer          #+#    #+#             */
/*   Updated: 2021/03/18 22:49:03 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_swap(t_all *all, int i, int j)
{
	t_sprite *sp;

	sp = all->spr[i];
	all->spr[i] = all->spr[j];
	all->spr[j] = sp;
}

void ft_qsort(t_all *all,int left, int right)
{

	t_sprite *pivot; // разрешающий элемент
  int l_hold = left; //левая граница
  int r_hold = right; // правая граница
  pivot = all->spr[left];
  while (left < right) // пока границы не сомкнутся
  {
    while ((all->spr[right]->dist <= pivot->dist) && (left < right))
      right--; // сдвигаем правую границу пока элемент [right] больше [pivot]
    if (left != right) // если границы не сомкнулись
    {
      all->spr[left] = all->spr[right]; // перемещаем элемент [right] на место разрешающего
      left++; // сдвигаем левую границу вправо
    }
    while ((all->spr[left]->dist >= pivot->dist) && (left < right))
      left++; // сдвигаем левую границу пока элемент [left] меньше [pivot]
    if (left != right) // если границы не сомкнулись
    {
      all->spr[right] = all->spr[left]; // перемещаем элемент [left] на место [right]
      right--; // сдвигаем правую границу вправо
    }
  }
  all->spr[left] = pivot; // ставим разрешающий элемент на место
  int tmp;
  tmp = left;
  left = l_hold;
  right = r_hold;
  if (left < tmp) // Рекурсивно вызываем сортировку для левой и правой части массива
    ft_qsort(all, left, tmp - 1);
  if (right > tmp)
    ft_qsort(all, tmp + 1, right);

	// int l = b, r = e;
	// int piv = all->spr[(l + r) / 2]->dist; // Опорным элементом для примера возьмём средний
	// while (l <= r)
	// {
	// 	while (all->spr[l]->dist < piv)
	// 		l++;
	// 	while (all->spr[r]->dist > piv)
	// 		r--;
	// 	if (l <= r)
	// 		ft_swap(all, l++, r--);
	// }
	// if (b < r)
	// 	ft_qsort (all, b, r);
	// if (e > l)
	// 	ft_qsort (all, l, e);
}

static	void		ft_sort_sprite2(t_all *all, t_sprite *sp)
{
	int				k;
	int				i;

	k = -1;
	while (all->spr[++k + 1])
	{
		i = -1;
		while (all->spr[++i + 1])
		{
			if (all->spr[i]->dist < all->spr[i + 1]->dist)
			{
				sp = all->spr[i];
				all->spr[i] = all->spr[i + 1];
				all->spr[i + 1] = sp;
				i = -1;
			}
		}
	}
}

void				ft_sort_sprite(t_all *all)
{
	int				k;
	int				i;
	t_sprite		*sp;

	k = -1;
	while (all->spr[++k])
	{
		all->spr[k]->dist = fabsf(((all->spr[k]->x - all->plr->x))
			* (cosf(all->plr->dir))
			+ ((all->plr->y - all->spr[k]->y)) * (sinf(all->plr->dir)));
		if (all->spr[k]->dist < 3.5)
			all->spr[k]->dist = sqrtf((all->spr[k]->x
				- all->plr->x) * (all->spr[k]->x - all->plr->x)
					+ (all->plr->y - all->spr[k]->y)
						* (all->plr->y - all->spr[k]->y));
	}
	ft_qsort(all, 0, all->win->count_2 - 1);
	//ft_sort_sprite2(all, sp);

	// i=0;
	// while (i < all->win->count_2)
	// {
	// 	printf("dist%d = %f\n", i +1, all->spr[i]->dist);
	// 	i++;
	// }

}

void				ft_paint_spr(t_all *all, t_drawsprite *drspr, int i)
{
	drspr->fsamplex = drspr->lx / drspr->fobjwidth;
	drspr->fsampley = drspr->ly / drspr->fobjheight;
	drspr->nobjcolumn = (int)(drspr->fmiddleobj + drspr->lx -
		(drspr->fobjwidth / 2.0f));
	if (drspr->nobjcolumn >= 0 && drspr->nobjcolumn < all->win->res_x)
	{
		drspr->color_spr = get_color_s(all->win, drspr->fsamplex *
			all->win->s_height, drspr->fsampley * all->win->s_width);
		if (drspr->color_spr > 1907485 &&
			(all->depthBuffer[all->win->res_x
				- drspr->nobjcolumn]) >= (all->spr[i]->dist) && all->spr[i]->dist < 15)
		{
			if (drspr->fobjceil + drspr->ly < all->win->res_y)
				my_mlx_pixel_put(all->win, all->win->res_x
					- drspr->nobjcolumn, drspr->fobjceil
						+ drspr->ly, drspr->color_spr);
		}
	}
}

void				ft_paint_sprite(t_all *all, t_drawsprite *drspr, int i)
{
	drspr->res_x = all->win->res_x;
	drspr->res_y = all->win->res_y;
	if (all->win->res_x < all->win->res_y)
	{
		drspr->res_x = all->win->res_y;
		drspr->res_y = all->win->res_x;
		drspr->kef = (float)((float)all->win->res_x / (float)all->win->res_y);
	}
	else
		drspr->kef = (float)((float)drspr->res_y / (float)all->win->res_x) + 0.05;
	drspr->fobjceil = (float)(drspr->res_y / 2.0)
		- drspr->res_y/ ((float)(all->spr[i]->dist));
	drspr->fobjfloor = drspr->res_y - drspr->fobjceil;
	//drspr->fobjFloor = ((float)all->win->res_x / 2) * (1 / tanf(FOV / 2)) - drspr->fobjCeil;
	drspr->fobjheight = (drspr->fobjfloor - drspr->fobjceil) * drspr->kef;
	drspr->fobjaspectratio = (float)all->win->s_height
		/ (float)all->win->s_width;
	drspr->fobjwidth = drspr->fobjheight / drspr->fobjaspectratio;
	drspr->fmiddleobj = (0.5f * (drspr->ang
		/ (FOV / 2.0f)) + 0.5f) * (float)all->win->res_x;
	drspr->lx = -1;
	drspr->ly = -1;
	while (++drspr->lx < drspr->fobjwidth)
	{
		drspr->ly = -1;
		while (++drspr->ly < drspr->fobjheight)
			ft_paint_spr(all, drspr, i);
	}
}

void				ft_draw_sprite(t_all *all, float angle)
{
	t_drawsprite	drawspr;
	int				i;

	angle -= 2 * (angle - M_PI_2);
	i = 0;
	while (all->spr[i])
	{
		drawspr.angle1 = atan2f(all->plr->y -
			all->spr[i]->y, all->plr->x - all->spr[i]->x);
		drawspr.angle2 = atan2f(sinf(angle), cosf(angle));
		drawspr.ang = drawspr.angle2 - drawspr.angle1;
		if (drawspr.ang > M_PI)
			drawspr.ang -= 2 * M_PI;
		else if (drawspr.ang < -M_PI)
			drawspr.ang += 2 * M_PI;
		if (fabs(drawspr.ang) < (FOV / 0.9) && all->spr[i]->dist > 1.0f)
			ft_paint_sprite(all, &drawspr, i);
		i++;
	}
}
