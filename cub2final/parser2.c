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
	if (all->win->count_2 > 0)
		ft_sort_sprite(all);
	ft_draw_player2(all, all->plr);
	mlx_put_image_to_window(all->win->mlx, all->win->win, all->win->img, 0, 0);
}

int				mouse(t_all *all)
{
	ft_freeall(all);
	exit(0);
}

void			ft_check_argv1(const char *argv1, t_all *all)
{
	if (ft_strlen(argv1) < 4)
		ft_perror("Error\n argv 1 incorrect by length\n", all);
	if (argv1[ft_strlen(argv1) - 4] != '.' || argv1[ft_strlen(argv1) - 3] !=
		'c' || argv1[ft_strlen(argv1) - 2] !=
			'u' || argv1[ft_strlen(argv1) - 1] != 'b')
		ft_perror("Error\n argv 1 not end by .cub\n", all);
}

void			ft_check_argv2(const char *argv2, t_all *all)
{
	if (ft_strlen(argv2) != 6)
		ft_perror("Error\n wrong length argv2\n", all);
	if (argv2[0] != '-' || argv2[1] != '-' || argv2[2] != 's'
		|| argv2[3] != 'a' || argv2[4] != 'v' || argv2[5] != 'e')
		ft_perror("Error\n argv 2 incorrect\n", all);
}
