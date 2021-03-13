/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 12:29:58 by cmarguer          #+#    #+#             */
/*   Updated: 2021/03/13 12:30:56 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int			get_color(t_win *win, int x, int y)
{
	char	*dst;
	int		color;

	dst = win->wall_addr + (x * (win->wall_bpp / 8)
		+ y * win->wall_line_length);
	color = *(unsigned int*)dst;
	return (color);
}

int			get_color_s(t_win *win, int x, int y)
{
	char	*dst;
	int		color;

	dst = win->S_addr + (x * (win->S_bpp / 8) + y * win->S_line_length);
	color = *(unsigned int*)dst;
	return (color);
}

void		my_mlx_pixel_put(t_win *win, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0)
		return ;
	dst = win->addr + (y * win->line_l + x * (win->bpp / 8));
	*(unsigned int*)dst = color;
}
