/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parcer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 20:48:08 by cmarguer          #+#    #+#             */
/*   Updated: 2021/03/19 20:48:11 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	void	ft_co_2(t_all *all, t_sprite *sprite, int i, int j)
{
	int k;

	k = 0;
	while (all->map[i])
	{
		j = 0;
		while (all->map[i][j] != '\0')
		{
			if (all->map[i][j] == '2')
			{
				sprite = malloc(sizeof(t_sprite));
				if (!sprite)
					ft_perror("Error\n with malloc buf for sprite\n", all);
				sprite->x = j + 0.5f;
				sprite->y = i + 0.5f;
				all->spr[k++] = sprite;
			}
			j++;
		}
		i++;
	}
}

void			ft_count_2(t_all *all)
{
	int			i;
	int			j;
	int			k;
	t_sprite	*sprite;

	i = 0;
	j = 0;
	all->win->count_2 = 0;
	while (all->map[i])
	{
		j = 0;
		while (all->map[i][j] != '\0')
		{
			if (all->map[i][j++] == '2')
				all->win->count_2++;
		}
		i++;
	}
	all->spr = ft_calloc(all->win->count_2, sizeof(t_sprite));
	if (all->spr == 0)
		ft_perror("Error\nwith malloc ft count 2", all);
	ft_co_2(all, sprite, 0, 0);
}

static	void	ft_parcer2(t_all *all, int i, int j)
{
	if (all->parcer_map[i][j] == 'R')
		ft_parcer_r(all, all->parcer_map[i], j + 1);
	else if (all->parcer_map[i][j] == 'N'
		&& all->parcer_map[i][j + 1] == 'O')
		ft_parcer_no(all, all->parcer_map[i], j + 2);
	else if (all->parcer_map[i][j] == 'S'
		&& all->parcer_map[i][j + 1] == 'O')
		ft_parcer_so(all, all->parcer_map[i], j + 2);
	else if (all->parcer_map[i][j] == 'W'
		&& all->parcer_map[i][j + 1] == 'E')
		ft_parcer_we(all, all->parcer_map[i], j + 2);
	else if (all->parcer_map[i][j] == 'E'
		&& all->parcer_map[i][j + 1] == 'A')
		ft_parcer_ea(all, all->parcer_map[i], j + 2);
	else if (all->parcer_map[i][j] == 'F')
		ft_parcer_f(all, all->parcer_map[i], j + 1);
	else if (all->parcer_map[i][j] == 'C')
		ft_parcer_c(all, all->parcer_map[i], j + 1);
	else if (all->parcer_map[i][j] == 'S')
		ft_parcer_s(all, all->parcer_map[i], j + 1);
}

void			ft_parcer(t_all *all)
{
	int			parametr;

	all->plr->i = -1;
	all->plr->j = 0;
	ft_preparcer(all);
	parametr = 0;
	while (all->parcer_map[++all->plr->i])
	{
		if (all->parcer_map[all->plr->i][all->plr->j] == '\0')
		{
			parametr--;
			continue ;
		}
		while (all->parcer_map[all->plr->i][all->plr->j] == ' ')
			all->plr->j++;
		ft_parcer2(all, all->plr->i, all->plr->j);
		if (all->parcer_map[all->plr->i][all->plr->j] == '1')
		{
			ft_parcer_map(all, all->plr->i);
			parametr += all->plr->i;
			break ;
		}
		all->plr->j = 0;
	}
	ft_afterparcer(all, parametr);
}
