/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parcer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 20:48:08 by cmarguer          #+#    #+#             */
/*   Updated: 2021/03/20 09:43:51 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	void	ft_count_2v2(t_all *all, t_sprite *sprite, int j, int k)
{
	int			i;

	i = 0;
	j = 0;
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
					ft_perror("Error\n");
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
	ft_count_2v2(all, sprite, 0, 0);
}

static	int		ft_parcer2(t_all *all, int i, int j, int parametr)
{
	if (all->parcer_map[i][j] == 'R')
		ft_parcer_r(all, all->parcer_map[i], j + 1);
	else if (all->parcer_map[i][j] == 'N' && all->parcer_map[i][j + 1] == 'O')
		ft_parcer_no(all, all->parcer_map[i], j + 2);
	else if (all->parcer_map[i][j] == 'S' && all->parcer_map[i][j + 1] == 'O')
		ft_parcer_so(all, all->parcer_map[i], j + 2);
	else if (all->parcer_map[i][j] == 'W' && all->parcer_map[i][j + 1] == 'E')
		ft_parcer_we(all, all->parcer_map[i], j + 2);
	else if (all->parcer_map[i][j] == 'E' && all->parcer_map[i][j + 1] == 'A')
		ft_parcer_ea(all, all->parcer_map[i], j + 2);
	else if (all->parcer_map[i][j] == 'F')
		ft_parcer_f(all, all->parcer_map[i], j + 1);
	else if (all->parcer_map[i][j] == 'C')
		ft_parcer_c(all, all->parcer_map[i], j + 1);
	else if (all->parcer_map[i][j] == 'S')
		ft_parcer_s(all, all->parcer_map[i], j + 1);
	else if (all->parcer_map[i][j] == '1')
	{
		ft_parcer_map(all, i);
		parametr += i;
		ft_afterparcer(all, parametr);
		return (1);
	}
	return (0);
}

void			ft_parcer(t_all *all)
{
	int			i;
	int			j;
	int			parametr;

	j = 0;
	i = -1;
	ft_preparcer(all);
	parametr = 0;
	while (all->parcer_map[++i])
	{
		if (all->parcer_map[i][j] == '\0')
		{
			parametr--;
			continue ;
		}
		while (all->parcer_map[i][j] == ' ')
			j++;
		if (ft_parcer2(all, i, j, parametr))
			break ;
		j = 0;
	}
}
