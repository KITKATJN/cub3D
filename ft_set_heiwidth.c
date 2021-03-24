/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_heiwidth.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 18:08:20 by cmarguer          #+#    #+#             */
/*   Updated: 2021/03/21 18:08:22 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_setheiwifth(t_all *all, int height, int width)
{
	if (all->win->res_y > height)
		all->win->res_y = height - 1;
	if (all->win->res_x > width)
		all->win->res_x = width - 1;
	if (all->win->res_x == 60 || all->win->res_x == 40)
		all->win->res_x++;
}

void	ft_checkamountaft(t_all *all, int check, int amount)
{
	if (check == 1)
		amount++;
	if (amount != 2)
		ft_perror("Error\n wrong number of parametr in r\n", all);
}
