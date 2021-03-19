/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pre_after_parcer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 01:31:26 by cmarguer          #+#    #+#             */
/*   Updated: 2021/03/20 02:25:19 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_preparcer(t_all *all)
{
	all->win->res_x = 0;
	all->win->res_y = 0;
	all->map = 0;
	all->win->c_color = -1;
	all->win->f_color = -1;
	all->win->s_path = 0;
	all->win->ea_path = 0;
	all->win->so_path = 0;
	all->win->we_path = 0;
	all->win->no_path = 0;
	all->plr->x = -1;
}

void	ft_afterparcer(t_all *all, int parametr)
{
	if (all->win->res_x == 0 || all->win->res_y == 0)
		ft_perror("Error\n");
	if (all->map == 0)
		ft_perror("Error\n");
	if (all->win->c_color == 0)
		ft_perror("Error\n");
	if (all->win->f_color == 0)
		ft_perror("Error\n");
	if (all->win->s_path == 0)
		ft_perror("Error\n");
	if (all->win->ea_path == 0)
		ft_perror("Error\n");
	if (all->win->so_path == 0)
		ft_perror("Error\n");
	if (all->win->we_path == 0)
		ft_perror("Error\n");
	if (parametr != 8)
		ft_perror("Error\n");
}
