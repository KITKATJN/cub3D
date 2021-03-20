/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 16:27:50 by cmarguer          #+#    #+#             */
/*   Updated: 2021/03/20 16:27:53 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			draw_screen(t_all *all)
{
	ft_sort_sprite(all);
	ft_draw_player2(all, all->plr);
	mlx_put_image_to_window(all->win->mlx, all->win->win, all->win->img, 0, 0);
}

int				mouse(int key, t_all *all)
{
	ft_freeall(all);
	exit(0);
}

void			ft_check_argv2(const char *argv2)
{
	if (ft_strlen(argv2) != 6)
		ft_perror("Error\n");
	if (argv2[0] != '-' || argv2[1] != '-' || argv2[2] != 's'
		|| argv2[3] != 'a' || argv2[4] != 'v' || argv2[5] != 'e')
		ft_perror("Error\n");
}
