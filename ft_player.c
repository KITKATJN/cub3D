/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 09:44:44 by cmarguer          #+#    #+#             */
/*   Updated: 2021/03/20 09:51:53 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			ft_plr_check(t_plr *plr)
{
	if (plr->x == -1)
		return ;
	else
		ft_perror("Error\n");
}

static	void	ft_set_plr_xy(t_plr *plr, t_point pos)
{
	plr->x = pos.x + 0.5;
	plr->y = pos.y + 0.5;
}

static	void	ft_set_plr(char **map, t_plr *plr, t_point pos)
{
	if (ft_strchr("N", map[pos.y][pos.x]))
	{
		ft_plr_check(plr);
		ft_set_plr_xy(plr, pos);
		plr->dir = 1 * M_PI_2;
	}
	if (ft_strchr("S", map[pos.y][pos.x]))
	{
		ft_plr_check(plr);
		ft_set_plr_xy(plr, pos);
		plr->dir = 3 * M_PI_2;
	}
	if (ft_strchr("W", map[pos.y][pos.x]))
	{
		ft_plr_check(plr);
		ft_set_plr_xy(plr, pos);
		plr->dir = M_PI;
	}
	if (ft_strchr("E", map[pos.y][pos.x]))
	{
		ft_plr_check(plr);
		ft_set_plr_xy(plr, pos);
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
			ft_set_plr(map, plr, pos);
			pos.x++;
		}
		pos.y++;
	}
}
