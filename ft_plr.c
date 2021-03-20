/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 15:51:54 by cmarguer          #+#    #+#             */
/*   Updated: 2021/03/20 15:51:56 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	void	ft_plr_check(t_plr *plr)
{
	if (plr->x == -1)
		return ;
	else
		ft_perror("Error\n");
}

static	void	set_plr_plr(t_plr *plr, t_point pos)
{
	plr->x = pos.x + 0.5;
	plr->y = pos.y + 0.5;
}

static	void	ft_plr_plr(char **map, t_plr *plr, t_point pos)
{
	if (ft_strchr("N", map[pos.y][pos.x]))
	{
		ft_plr_check(plr);
		set_plr_plr(plr, pos);
		plr->dir = 1 * M_PI_2;
	}
	if (ft_strchr("S", map[pos.y][pos.x]))
	{
		ft_plr_check(plr);
		set_plr_plr(plr, pos);
		plr->dir = 3 * M_PI_2;
	}
	if (ft_strchr("W", map[pos.y][pos.x]))
	{
		ft_plr_check(plr);
		set_plr_plr(plr, pos);
		plr->dir = M_PI;
	}
	if (ft_strchr("E", map[pos.y][pos.x]))
	{
		ft_plr_check(plr);
		set_plr_plr(plr, pos);
		plr->dir = 0;
	}
}

void			ft_init_plr(char **map, t_plr *plr)
{
	t_point		pos;

	ft_bzero(&pos, sizeof(t_point));
	while (map[pos.y])
	{
		pos.x = 0;
		while (map[pos.y][pos.x])
		{
			ft_plr_plr(map, plr, pos);
			pos.x++;
		}
		pos.y++;
	}
}
